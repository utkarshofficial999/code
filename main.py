import argparse
import sys
from pathlib import Path

# Force UTF-8 on Windows consoles to prevent cp1252 charmap encoding errors
if sys.platform.startswith("win"):
    try:
        sys.stdout.reconfigure(encoding="utf-8")
        sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

from rich.console import Console
from rich.table import Table
from rich.panel import Panel

from agent import LeetCodeAgent
from roadmap import RoadmapManager
from tracker import ProgressTracker
from leetcode_client import LeetCodeClient
from scheduler import DaemonScheduler
from config import LEETCODE_SESSION, LEETCODE_CSRFTOKEN, GEMINI_API_KEY, SCHEDULE_TIMES

console = Console(force_terminal=True, legacy_windows=False)


def cmd_status():
    roadmap = RoadmapManager()
    tracker = ProgressTracker()
    solved_slugs = tracker.get_solved_slugs()
    stats = roadmap.get_stats(solved_slugs)

    total = stats["total_problems"]
    solved = stats["total_solved"]
    percent = stats["overall_percent"]

    # Header Panel
    console.print(Panel(
        f"[bold cyan]NeetCode 250 DSA Master Tracker[/bold cyan]\n"
        f"Completed: [bold green]{solved}[/bold green] / [bold white]{total}[/bold white] problems ([bold yellow]{percent}%[/bold yellow])\n"
        f"Remaining: [bold red]{total - solved}[/bold red] problems",
        title="[bold blue]Overall Progress[/bold blue]"
    ))

    # Topic Breakdown Table
    table = Table(title="Topic-wise Roadmap Progression", show_header=True, header_style="bold magenta")
    table.add_column("Category / Topic", style="white", width=26)
    table.add_column("Solved / Total", justify="center", style="cyan", width=16)
    table.add_column("Progress", style="green", width=25)
    table.add_column("Status", justify="center", width=14)

    for cat_name, cat_data in stats["categories"].items():
        c_solved = cat_data["solved"]
        c_total = cat_data["total"]
        c_pct = cat_data["percent"]

        # Clean bar
        filled_len = int(c_pct / 5)
        bar = "#" * filled_len + "-" * (20 - filled_len)
        progress_str = f"[{bar}] {c_pct:.0f}%"

        if c_solved == c_total and c_total > 0:
            status = "[bold green]COMPLETED[/bold green]"
        elif c_solved > 0:
            status = "[bold yellow]IN PROGRESS[/bold yellow]"
        else:
            status = "[dim]PENDING[/dim]"

        table.add_row(cat_name, f"{c_solved} / {c_total}", progress_str, status)

    console.print(table)

    # Recent Solved Table
    recent = tracker.get_recent_solutions(limit=5)
    if recent:
        r_table = Table(title="Recent Solved Submissions", show_header=True, header_style="bold blue")
        r_table.add_column("Problem", style="white")
        r_table.add_column("Category", style="cyan")
        r_table.add_column("Difficulty", style="yellow")
        r_table.add_column("Verdict", style="green")
        r_table.add_column("Solved At", style="dim")

        for r in recent:
            diff_color = "green" if r.get("difficulty") == "Easy" else ("yellow" if r.get("difficulty") == "Medium" else "red")
            r_table.add_row(
                r.get("name", "N/A"),
                r.get("category", "N/A"),
                f"[{diff_color}]{r.get('difficulty', 'N/A')}[/{diff_color}]",
                r.get("status", "Accepted"),
                r.get("solved_at", "")[:19].replace("T", " ")
            )
        console.print(r_table)

def cmd_topics():
    roadmap = RoadmapManager()
    tracker = ProgressTracker()
    solved_slugs = tracker.get_solved_slugs()

    table = Table(title="NeetCode 250 Topics & Question Counts", show_header=True, header_style="bold magenta")
    table.add_column("#", style="dim", width=4)
    table.add_column("Category Topic", style="bold cyan")
    table.add_column("Total Questions", justify="center", style="white", width=18)
    table.add_column("Unsolved", justify="center", style="yellow", width=12)

    categories = roadmap.get_all_categories()
    for idx, cat in enumerate(categories, 1):
        probs = roadmap.get_problems_by_category(cat)
        unsolved_count = len([p for p in probs if p["leetcode_slug"] not in solved_slugs])
        table.add_row(str(idx), cat, str(len(probs)), str(unsolved_count))

    console.print(table)

def cmd_check_auth():
    console.print(Panel("[bold cyan]LeetCode & AI API Verification[/bold cyan]", title="System Check"))

    # 1. Check AI Provider (Groq / Gemini / OpenAI)
    from config import GROQ_API_KEY, GROQ_MODEL
    if GROQ_API_KEY:
        console.print(f"  [green]✓[/green] GROQ_API_KEY: Configured (Model: [bold cyan]{GROQ_MODEL}[/bold cyan])")
    elif GEMINI_API_KEY:
        console.print("  [green]✓[/green] GEMINI_API_KEY: Configured")
    else:
        console.print("  [yellow]![/yellow] AI API Key: [bold red]Missing[/bold red] in .env (add GROQ_API_KEY or GEMINI_API_KEY)")


    # 2. Check LeetCode
    client = LeetCodeClient()
    if client.is_authenticated():
        console.print("  [green]✓[/green] LEETCODE_SESSION & CSRFTOKEN: Configured in .env")
        console.print("  Checking live LeetCode login status...")
        status = client.check_user_status()
        if status.get("is_signed_in"):
            console.print(f"  [bold green]✓ Successfully authenticated as LeetCode user: {status.get('username')}[/bold green] (Premium: {status.get('is_premium')})")
        else:
            console.print(f"  [bold yellow]! Session cookie was rejected by LeetCode: {status.get('error', 'Not signed in')}[/bold yellow]")
    else:
        console.print("  [yellow]![/yellow] LEETCODE_SESSION: [bold red]Not set[/bold red] in .env")
        console.print("    (Agent will solve problems locally and generate C++ files until session cookies are added)")

def cmd_solve(count: int = 1, topic: str = None, notify: bool = True):
    agent = LeetCodeAgent()
    results = agent.run_solve_cycle(count=count, target_topic=topic)
    if notify and results:
        try:
            from telegram_bot import send_full_problem_solution
            for r in results:
                send_full_problem_solution(r)
        except Exception as e:
            console.print(f"[dim]Telegram notification skipped: {e}[/dim]")

def cmd_daemon(run_now: bool = False):
    scheduler = DaemonScheduler()
    scheduler.start(run_immediately=run_now)

def main():
    parser = argparse.ArgumentParser(
        description="LeetCode NeetCode 250 DSA Automated Solving Agent"
    )
    subparsers = parser.add_subparsers(dest="command", help="Available subcommands")

    # Run / Solve command
    solve_parser = subparsers.add_parser("solve", help="Solve questions immediately")
    solve_parser.add_argument("-c", "--count", type=int, default=3, help="Number of questions to solve (default: 3)")
    solve_parser.add_argument("-t", "--topic", type=str, default=None, help="Target specific topic (e.g. 'Arrays & Hashing')")
    solve_parser.add_argument("--no-notify", action="store_true", help="Do not send Telegram notification")

    # Daemon command
    daemon_parser = subparsers.add_parser("daemon", help="Start background 24-hr multi-time daemon")
    daemon_parser.add_argument("--now", action="store_true", help="Run 1 solve cycle immediately on startup")

    # Status command
    subparsers.add_parser("status", help="Show NeetCode 250 roadmap progression and stats")

    # Topics command
    subparsers.add_parser("topics", help="List all 18 topics and question counts")

    # Check-auth command
    subparsers.add_parser("check-auth", help="Verify LeetCode session and Gemini API credentials")

    # Reset command
    reset_parser = subparsers.add_parser("reset", help="Reset tracking database")
    # Telegram bot command
    subparsers.add_parser("bot", help="Run Telegram Bot listener standalone")

    args = parser.parse_args()

    if args.command == "solve":
        cmd_solve(count=args.count, topic=args.topic, notify=not args.no_notify)
    elif args.command == "daemon":
        cmd_daemon(run_now=args.now)
    elif args.command == "bot":
        from telegram_bot import TelegramBotService
        bot = TelegramBotService()
        bot.start_polling()
    elif args.command == "status":
        cmd_status()
    elif args.command == "topics":
        cmd_topics()
    elif args.command == "check-auth":
        cmd_check_auth()
    elif args.command == "reset":

        if args.confirm:
            from config import PROGRESS_FILE
            if PROGRESS_FILE.exists():
                PROGRESS_FILE.unlink()
            console.print("[bold green]Progress reset successfully.[/bold green]")
        else:
            console.print("[yellow]Please pass --confirm to reset progress.[/yellow]")
    else:
        # Default action: show status and quick help
        cmd_status()
        console.print(
            "\n[dim]Run [bold white]python main.py --help[/bold white] or [bold white]python main.py solve -c 3[/bold white] to solve questions.[/dim]"
        )

if __name__ == "__main__":
    main()
