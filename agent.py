import time
import sys
from typing import Dict, Any, List, Optional

if sys.platform.startswith("win"):
    try:
        sys.stdout.reconfigure(encoding="utf-8")
        sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

from rich.console import Console
from rich.table import Table
from rich.panel import Panel
from rich.progress import Progress, SpinnerColumn, TextColumn

from roadmap import RoadmapManager
from tracker import ProgressTracker
from leetcode_client import LeetCodeClient
from solver import ProblemSolver
from solution_saver import SolutionSaver
from config import QUESTIONS_PER_SCHEDULE_RUN

console = Console(force_terminal=True, legacy_windows=False)


class LeetCodeAgent:
    def __init__(self):
        self.roadmap = RoadmapManager()
        self.tracker = ProgressTracker()
        self.client = LeetCodeClient()
        self.solver = ProblemSolver()
        self.saver = SolutionSaver()

    def run_solve_cycle(self, count: int = 1, target_topic: Optional[str] = None) -> List[Dict[str, Any]]:
        """
        Executes a solve cycle for `count` questions topic-wise.
        """
        solved_slugs = self.tracker.get_solved_slugs()
        next_problems = self.roadmap.get_next_topic_questions(
            solved_slugs=solved_slugs,
            count=count,
            target_topic=target_topic
        )

        if not next_problems:
            console.print("[bold green]All 250 problems in the NeetCode roadmap have been solved! Congratulations![/bold green]")
            return []

        console.print(Panel.fit(
            f"[bold cyan]LeetCode NeetCode 250 Agent[/bold cyan]\n"
            f"Selected [bold yellow]{len(next_problems)}[/bold yellow] topic-wise problem(s) to solve:\n" +
            "\n".join([f"  • [bold]{p['name']}[/bold] ({p['category']} | {p['difficulty']})" for p in next_problems]),
            title="[bold blue]Solve Cycle Started[/bold blue]"
        ))

        results = []
        for idx, problem in enumerate(next_problems, 1):
            console.print(f"\n[bold magenta]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[/bold magenta]")
            console.print(f"[bold white]Problem {idx}/{len(next_problems)}: [/bold white][bold yellow]{problem['name']}[/bold yellow] ({problem['category']})")
            
            res = self.solve_single_problem(problem)
            results.append(res)
            
            # Short cooldown between consecutive problems
            if idx < len(next_problems):
                time.sleep(2)

        return results

    def solve_single_problem(self, problem_meta: Dict[str, Any]) -> Dict[str, Any]:
        slug = problem_meta["leetcode_slug"]
        
        # 1. Fetch live problem details from LeetCode
        with Progress(SpinnerColumn(), TextColumn("[progress.description]{task.description}"), transient=True) as progress:
            progress.add_task(description=f"Fetching details for [cyan]{slug}[/cyan] from LeetCode...", total=None)
            question_detail = self.client.fetch_question(slug)

        if not question_detail:
            console.print(f"[bold red]✗ Failed to fetch question details for {slug}[/bold red]")
            return {"success": False, "slug": slug, "error": "Fetch failed"}

        console.print(f"  [green]✓[/green] Fetched: [bold]{question_detail['title']}[/bold] (Difficulty: [bold]{question_detail['difficulty']}[/bold])")

        # 2. Check if LLM solver is configured
        if not self.solver.is_configured():
            console.print(
                "[bold yellow]! Warning:[/bold yellow] No LLM API key detected (GEMINI_API_KEY / OPENAI_API_KEY).\n"
                "  Please set [bold green]GEMINI_API_KEY[/bold green] in your [cyan].env[/cyan] file to enable AI auto-solving."
            )
            # Create a clean starter solution file for the user
            fallback_solve = {
                "success": False,
                "code": question_detail["cpp_starter"],
                "intuition": "Configure GEMINI_API_KEY in .env for automated AI solution generation.",
                "approach": "Awaiting API key configuration.",
                "time_complexity": "N/A",
                "space_complexity": "N/A"
            }
            sub_res = {
                "success": False,
                "status_msg": "API Key Required",
                "status_runtime": "N/A",
                "status_memory": "N/A"
            }
            saved_path = self.saver.save_solution(problem_meta, question_detail, fallback_solve, sub_res)
            return {"success": False, "slug": slug, "saved_path": str(saved_path)}

        # 3. Generate optimal C++ solution with retry loop
        max_attempts = 3
        solve_result = None
        submission_result = None
        previous_error = None

        for attempt in range(1, max_attempts + 1):
            with Progress(SpinnerColumn(), TextColumn("[progress.description]{task.description}"), transient=True) as progress:
                desc = f"Generating optimal C++ solution (Attempt {attempt}/{max_attempts})..." if attempt == 1 else f"Refining solution based on error feedback (Attempt {attempt}/{max_attempts})..."
                progress.add_task(description=desc, total=None)
                solve_result = self.solver.solve(question_detail, previous_error=previous_error)

            if not solve_result.get("success"):
                console.print(f"[bold red]✗ Solver failed: {solve_result.get('error', 'Unknown')}[/bold red]")
                break

            console.print(f"  [green]✓[/green] Generated C++ solution with Time: [bold]{solve_result.get('time_complexity')}[/bold], Space: [bold]{solve_result.get('space_complexity')}[/bold]")

            # 4. Submit to LeetCode if authenticated
            if self.client.is_authenticated():
                with Progress(SpinnerColumn(), TextColumn("[progress.description]{task.description}"), transient=True) as progress:
                    progress.add_task(description=f"Submitting to LeetCode and awaiting verdict...", total=None)
                    submission_result = self.client.submit_solution(
                        title_slug=slug,
                        question_id=question_detail["question_id"],
                        code=solve_result["code"]
                    )

                status_msg = submission_result.get("status_msg", "Unknown")
                if submission_result.get("success"):
                    console.print(f"  [bold green]✓ LeetCode Verdict: Accepted![/bold green] (Runtime: {submission_result.get('status_runtime')}, Memory: {submission_result.get('status_memory')})")
                    break
                else:
                    console.print(f"  [bold yellow]✗ LeetCode Verdict: {status_msg}[/bold yellow]")
                    # Compile error feedback for retry
                    err_details = []
                    if submission_result.get("compile_error"):
                        err_details.append(f"Compile Error:\n{submission_result['compile_error']}")
                    if submission_result.get("last_testcase"):
                        err_details.append(f"Failed Input:\n{submission_result['last_testcase']}")
                        err_details.append(f"Expected:\n{submission_result.get('expected_output')}")
                        err_details.append(f"Got:\n{submission_result.get('code_output')}")
                    previous_error = "\n".join(err_details) if err_details else status_msg
            else:
                submission_result = {
                    "success": True,
                    "status_msg": "Solved Locally (No LeetCode session token in .env)",
                    "status_runtime": "Local",
                    "status_memory": "Local"
                }
                console.print("  [cyan]ℹ Saved locally (add LEETCODE_SESSION and LEETCODE_CSRFTOKEN in .env to enable live submissions).[/cyan]")
                break

        # 5. Save solution file locally
        if not solve_result or not solve_result.get("success"):
            submission_result = {
                "success": False,
                "status_msg": "Generation Failed",
                "status_runtime": "N/A",
                "status_memory": "N/A"
            }
            if not solve_result:
                solve_result = {
                    "code": question_detail["cpp_starter"],
                    "intuition": "LLM generation failed.",
                    "approach": "N/A",
                    "time_complexity": "N/A",
                    "space_complexity": "N/A"
                }

        saved_path = self.saver.save_solution(problem_meta, question_detail, solve_result, submission_result or {})
        console.print(f"  [green]✓ Saved to:[/green] [dim]{saved_path}[/dim]")

        # 6. Record progress only on valid solved solution
        if solve_result.get("success") and submission_result and (submission_result.get("success") or submission_result.get("status_msg", "").startswith("Solved Locally")):
            self.tracker.record_solution(
                slug=slug,
                problem_meta=problem_meta,
                submission_result=submission_result,
                solution_path=str(saved_path)
            )


        return {
            "success": submission_result.get("success") if submission_result else False,
            "slug": slug,
            "name": problem_meta["name"],
            "category": problem_meta["category"],
            "status": submission_result.get("status_msg") if submission_result else "Unknown",
            "saved_path": str(saved_path)
        }
