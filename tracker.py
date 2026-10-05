import json
from datetime import datetime
from pathlib import Path
from typing import Dict, Any, Set, List
from config import PROGRESS_FILE

class ProgressTracker:
    def __init__(self, filepath: Path = PROGRESS_FILE):
        self.filepath = filepath
        self.data: Dict[str, Any] = {
            "solved": {},          # slug -> metadata (timestamp, submission_id, status, runtime, memory, solution_file)
            "history": [],         # list of run logs
            "created_at": datetime.now().isoformat(),
            "last_updated": datetime.now().isoformat()
        }
        self._load()

    def _load(self):
        if self.filepath.exists():
            try:
                with open(self.filepath, "r", encoding="utf-8") as f:
                    self.data = json.load(f)
            except Exception as e:
                print(f"[Tracker] Warning: could not parse {self.filepath}, starting fresh: {e}")

    def save(self):
        self.data["last_updated"] = datetime.now().isoformat()
        with open(self.filepath, "w", encoding="utf-8") as f:
            json.dump(self.data, f, indent=2)

    def get_solved_slugs(self) -> Set[str]:
        self._load()
        return set(self.data.get("solved", {}).keys())

    def record_solution(self, slug: str, problem_meta: Dict[str, Any], submission_result: Dict[str, Any], solution_path: str):
        self._load()
        self.data["solved"][slug] = {
            "slug": slug,
            "name": problem_meta.get("name"),
            "category": problem_meta.get("category"),
            "difficulty": problem_meta.get("difficulty"),
            "solved_at": datetime.now().isoformat(),
            "status": submission_result.get("status_msg", "Accepted"),
            "submission_id": submission_result.get("submission_id"),
            "runtime": submission_result.get("status_runtime", "N/A"),
            "memory": submission_result.get("status_memory", "N/A"),
            "solution_path": solution_path
        }
        self.save()

    def log_run(self, details: Dict[str, Any]):
        self._load()
        details["timestamp"] = datetime.now().isoformat()
        self.data.setdefault("history", []).append(details)
        self.save()

    def is_solved(self, slug: str) -> bool:
        self._load()
        return slug in self.data.get("solved", {})

    def get_recent_solutions(self, limit: int = 10) -> List[Dict[str, Any]]:
        self._load()
        solved_list = list(self.data.get("solved", {}).values())
        solved_list.sort(key=lambda x: x.get("solved_at", ""), reverse=True)
        return solved_list[:limit]

