"""
Cross-platform / Python wrapper for configuring Windows Task Scheduler for the LeetCode Agent.
"""

import sys
import subprocess
from pathlib import Path
import argparse

BASE_DIR = Path(__file__).resolve().parent
PS1_SCRIPT = BASE_DIR / "setup_scheduler.ps1"

def run_ps1(action: str, times: str = ""):
    cmd = [
        "powershell",
        "-NoProfile",
        "-ExecutionPolicy", "Bypass",
        "-File", str(PS1_SCRIPT),
        "-Action", action
    ]
    if times:
        cmd.extend(["-Times", times])

    result = subprocess.run(cmd, cwd=str(BASE_DIR))
    return result.returncode

def main():
    parser = argparse.ArgumentParser(description="Configure Windows Task Scheduler for LeetCode Auto-Solver")
    parser.add_argument("--action", choices=["install", "uninstall", "list", "runnow"], default="install", help="Action to perform")
    parser.add_argument("--times", type=str, default="", help="Comma-separated 24hr times (e.g. '09:00,15:45,16:15')")
    args = parser.parse_args()

    sys.exit(run_ps1(args.action, args.times))

if __name__ == "__main__":
    main()
