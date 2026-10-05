import json
from pathlib import Path
from typing import List, Dict, Optional, Any
from config import DATA_FILE

ORDERED_CATEGORIES = [
    "Arrays & Hashing",
    "Two Pointers",
    "Sliding Window",
    "Stack",
    "Binary Search",
    "Linked List",
    "Trees",
    "Heap / Priority Queue",
    "Backtracking",
    "Tries",
    "Graphs",
    "Advanced Graphs",
    "1-D Dynamic Programming",
    "2-D Dynamic Programming",
    "Greedy",
    "Intervals",
    "Math & Geometry",
    "Bit Manipulation"
]

class RoadmapManager:
    def __init__(self, data_file: Path = DATA_FILE):
        self.data_file = data_file
        self.problems: List[Dict[str, Any]] = []
        self._load_data()

    def _load_data(self):
        if not self.data_file.exists():
            raise FileNotFoundError(f"Master dataset not found at {self.data_file}")
        with open(self.data_file, "r", encoding="utf-8") as f:
            data = json.load(f)
            self.problems = data.get("problems", [])

    def get_all_categories(self) -> List[str]:
        # Return categories respecting ORDERED_CATEGORIES order
        available = set(p["category"] for p in self.problems)
        ordered = [c for c in ORDERED_CATEGORIES if c in available]
        # Append any remaining not in ORDERED_CATEGORIES
        for c in sorted(available):
            if c not in ordered:
                ordered.append(c)
        return ordered

    def get_problems_by_category(self, category: str) -> List[Dict[str, Any]]:
        return [p for p in self.problems if p["category"].lower() == category.lower()]

    def get_problem_by_slug(self, slug: str) -> Optional[Dict[str, Any]]:
        for p in self.problems:
            if p["leetcode_slug"] == slug or p.get("slug") == slug:
                return p
        return None

    def get_next_topic_questions(self, solved_slugs: set, count: int = 3, target_topic: Optional[str] = None) -> List[Dict[str, Any]]:
        """
        Picks the next `count` questions topic-wise according to the NeetCode roadmap.
        If target_topic is specified, picks strictly from that topic.
        Otherwise, picks from the current earliest topic with unsolved questions.
        If a topic has fewer than `count` questions left, it rolls into the next topic.
        """
        selected: List[Dict[str, Any]] = []
        categories = [target_topic] if target_topic else self.get_all_categories()

        for cat in categories:
            cat_problems = self.get_problems_by_category(cat)
            unsolved = [p for p in cat_problems if p["leetcode_slug"] not in solved_slugs]
            
            for p in unsolved:
                selected.append(p)
                if len(selected) >= count:
                    return selected

        return selected

    def get_stats(self, solved_slugs: set) -> Dict[str, Any]:
        total = len(self.problems)
        solved_count = len([p for p in self.problems if p["leetcode_slug"] in solved_slugs])
        
        category_stats = {}
        for cat in self.get_all_categories():
            cat_probs = self.get_problems_by_category(cat)
            cat_total = len(cat_probs)
            cat_solved = len([p for p in cat_probs if p["leetcode_slug"] in solved_slugs])
            category_stats[cat] = {
                "total": cat_total,
                "solved": cat_solved,
                "percent": round((cat_solved / cat_total * 100), 1) if cat_total > 0 else 0
            }

        return {
            "total_problems": total,
            "total_solved": solved_count,
            "overall_percent": round((solved_count / total * 100), 1) if total > 0 else 0,
            "categories": category_stats
        }
