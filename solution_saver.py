import re
from pathlib import Path
from typing import Dict, Any
from config import SOLUTIONS_DIR

def sanitize_dirname(name: str) -> str:
    cleaned = name.replace("&", "and")
    cleaned = re.sub(r'[^a-zA-Z0-9_\- ]', '', cleaned)
    cleaned = cleaned.strip().replace(' ', '_').lower()
    cleaned = re.sub(r'_+', '_', cleaned)
    return cleaned


class SolutionSaver:
    def __init__(self, base_dir: Path = SOLUTIONS_DIR):
        self.base_dir = base_dir

    def save_solution(
        self,
        problem_meta: Dict[str, Any],
        question_detail: Dict[str, Any],
        solve_result: Dict[str, Any],
        submission_result: Dict[str, Any]
    ) -> Path:
        category = problem_meta.get("category", "General")
        cat_dir = self.base_dir / sanitize_dirname(category)
        cat_dir.mkdir(parents=True, exist_ok=True)

        frontend_id = question_detail.get("frontend_id", "0").zfill(3)
        slug = sanitize_dirname(problem_meta.get("leetcode_slug", "solution"))
        filename = f"{frontend_id}_{slug}.cpp"
        file_path = cat_dir / filename

        status_msg = submission_result.get("status_msg", "Accepted")
        runtime = submission_result.get("status_runtime", "N/A")
        memory = submission_result.get("status_memory", "N/A")
        title = question_detail.get("title", problem_meta.get("name", ""))
        difficulty = question_detail.get("difficulty", problem_meta.get("difficulty", ""))
        leetcode_url = problem_meta.get("leetcode_url", f"https://leetcode.com/problems/{slug}/")
        neetcode_url = problem_meta.get("neetcode_url", "")
        
        intuition = solve_result.get("intuition", "")
        approach = solve_result.get("approach", "")
        time_comp = solve_result.get("time_complexity", "")
        space_comp = solve_result.get("space_complexity", "")
        cpp_code = solve_result.get("code", "")

        header_lines = [
            "/**",
            f" * NeetCode 250 - {category}",
            f" * Problem: {title} (LeetCode #{frontend_id})",
            f" * Difficulty: {difficulty}",
            f" * LeetCode URL: {leetcode_url}",
        ]
        if neetcode_url:
            header_lines.append(f" * NeetCode URL: {neetcode_url}")
        header_lines.extend([
            f" * Status: {status_msg} (Runtime: {runtime}, Memory: {memory})",
            " *",
            " * --- Intuition ---",
        ])
        for line in intuition.split("\n"):
            header_lines.append(f" * {line.strip()}")
        
        header_lines.extend([
            " *",
            " * --- Approach ---",
        ])
        for line in approach.split("\n"):
            header_lines.append(f" * {line.strip()}")

        header_lines.extend([
            " *",
            f" * --- Complexity ---",
            f" * Time Complexity:  {time_comp}",
            f" * Space Complexity: {space_comp}",
            " */",
            "",
            "#include <iostream>",
            "#include <vector>",
            "#include <string>",
            "#include <unordered_map>",
            "#include <unordered_set>",
            "#include <queue>",
            "#include <stack>",
            "#include <algorithm>",
            "#include <cmath>",
            "using namespace std;",
            "",
            cpp_code,
            ""
        ])

        content = "\n".join(header_lines)
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(content)

        return file_path
