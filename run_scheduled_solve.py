"""
LeetCode NeetCode 250 - Automated Scheduled Solve Runner
Executes a solve cycle, rebuilds docs/data.json, commits & pushes to GitHub,
and delivers full Telegram notifications. Designed for Windows Task Scheduler.
"""

import sys
import os
import time
import random
import logging
import argparse
import subprocess
from pathlib import Path
from datetime import datetime

# Force UTF-8 on Windows
if sys.platform.startswith("win"):
    try:
        sys.stdout.reconfigure(encoding="utf-8")
        sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

BASE_DIR = Path(__file__).resolve().parent
sys.path.insert(0, str(BASE_DIR))

from config import (
    LOGS_DIR,
    RANDOM_JITTER_MINUTES,
    QUESTIONS_PER_SCHEDULE_RUN,
    SCHEDULE_TIMES
)
from agent import LeetCodeAgent
from build_dashboard import build_data

# Ensure logs dir exists
LOGS_DIR.mkdir(parents=True, exist_ok=True)
log_file = LOGS_DIR / "scheduler.log"

logging.basicConfig(
    filename=str(log_file),
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)
logger = logging.getLogger("TaskScheduler")


def run_git_push(commit_msg: str) -> bool:
    """Stages solutions, progress, and docs, commits and pushes to origin."""
    try:
        # 1. Stage updated directories and progress
        subprocess.run(["git", "add", "solutions/", "progress.json", "docs/"], cwd=str(BASE_DIR), check=True)

        # 2. Check if anything is staged
        status_res = subprocess.run(
            ["git", "diff", "--staged", "--quiet"],
            cwd=str(BASE_DIR)
        )
        if status_res.returncode == 0:
            logger.info("Git: No changes detected to commit.")
            return True

        # 3. Commit
        subprocess.run(
            ["git", "commit", "-m", commit_msg],
            cwd=str(BASE_DIR),
            check=True
        )
        logger.info(f"Git: Committed changes: {commit_msg}")

        # 4. Push to remote
        push_res = subprocess.run(
            ["git", "push", "origin", "main"],
            cwd=str(BASE_DIR),
            capture_output=True,
            text=True
        )
        if push_res.returncode == 0:
            logger.info("Git: Successfully pushed to origin/main.")
            return True
        else:
            logger.error(f"Git push failed: {push_res.stderr}")
            return False
    except Exception as e:
        logger.error(f"Git operation encountered error: {e}")
        return False


def main():
    parser = argparse.ArgumentParser(description="Run LeetCode Auto-Solve cycle via Windows Task Scheduler")
    parser.add_argument("--slot", type=str, default="Manual/Task", help="Time slot label (e.g. 09:00, 15:45)")
    parser.add_argument("-c", "--count", type=int, default=QUESTIONS_PER_SCHEDULE_RUN, help="Questions count")
    parser.add_argument("--no-jitter", action="store_true", help="Skip random jitter delay")
    parser.add_argument("--no-push", action="store_true", help="Skip git push")
    args = parser.parse_args()

    slot_time = args.slot
    logger.info(f"--- Task Triggered for Slot [{slot_time}] ---")

    # 1. Optional jitter delay
    if not args.no_jitter and RANDOM_JITTER_MINUTES > 0:
        jitter_secs = random.randint(0, RANDOM_JITTER_MINUTES * 60)
        logger.info(f"Slot {slot_time}: applying random jitter delay of {jitter_secs // 60}m {jitter_secs % 60}s...")
        time.sleep(jitter_secs)

    try:
        # 2. Run solve cycle
        logger.info(f"Starting solve cycle for slot {slot_time} ({datetime.now().strftime('%Y-%m-%d %H:%M:%S')})...")
        agent = LeetCodeAgent()
        results = agent.run_solve_cycle(count=args.count)

        if not results:
            logger.info("Solve cycle returned no results (or all problems already solved).")
            return

        logger.info(f"Solve cycle completed with {len(results)} problem(s): {results}")

        # 3. Send Telegram Notification
        try:
            from telegram_bot import send_full_problem_solution, send_telegram_message
            send_telegram_message(f"⏰ <b>Scheduled Solve Executed! ({slot_time})</b>")
            for r in results:
                send_full_problem_solution(r)
        except Exception as te:
            logger.warning(f"Telegram notification warning: {te}")

        # 4. Rebuild Web Dashboard Data
        try:
            build_data()
            logger.info("Dashboard data successfully refreshed at docs/data.json.")
        except Exception as be:
            logger.error(f"Failed to rebuild dashboard data: {be}")

        # 5. Git Commit & Push
        if not args.no_push:
            solved_names = ", ".join([r.get("name", "Problem") for r in results if r.get("success")])
            if not solved_names:
                solved_names = results[0].get("name", "NeetCode 250 Problem")
            commit_msg = f"Auto-solve: {solved_names} solved & dashboard refresh"
            run_git_push(commit_msg)

        logger.info(f"--- Task Completed Successfully for Slot [{slot_time}] ---")

    except Exception as e:
        logger.error(f"Fatal error during scheduled solve: {e}", exc_info=True)
        try:
            from telegram_bot import send_telegram_message
            send_telegram_message(f"⚠️ <b>LeetCode Auto-Solver Error ({slot_time}):</b>\n<code>{str(e)[:300]}</code>")
        except Exception:
            pass
        sys.exit(1)


if __name__ == "__main__":
    main()
