import sys
import os
import time
import requests
import json
import logging
import html
import re
import threading
import subprocess
from typing import Optional, Dict, Any
from pathlib import Path

# Force UTF-8 on Windows consoles to prevent cp1252 charmap encoding errors
if sys.platform.startswith("win"):
    try:
        sys.stdout.reconfigure(encoding="utf-8")
        sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

from config import TELEGRAM_BOT_TOKEN, TELEGRAM_CHAT_ID, BASE_DIR, ENV_PATH
from agent import LeetCodeAgent
from roadmap import RoadmapManager
from tracker import ProgressTracker
from build_dashboard import build_data

API_BASE = f"https://api.telegram.org/bot{TELEGRAM_BOT_TOKEN}"
DASHBOARD_URL = "https://utkarshofficial999.github.io/code/"


def save_chat_id(chat_id: str):
    """Saves chat_id to .env file so it persists."""
    if not ENV_PATH.exists():
        return
    try:
        content = ENV_PATH.read_text(encoding="utf-8")
        if "TELEGRAM_CHAT_ID=" in content:
            content = re.sub(r'TELEGRAM_CHAT_ID=.*', f'TELEGRAM_CHAT_ID={chat_id}', content)
        else:
            content += f"\nTELEGRAM_CHAT_ID={chat_id}\n"
        ENV_PATH.write_text(content, encoding="utf-8")
    except Exception as e:
        print(f"[Telegram] Failed to save chat_id: {e}")


def git_commit_and_push(commit_msg: str) -> bool:
    """Stages solutions, progress, and docs, commits and pushes to origin."""
    try:
        subprocess.run(["git", "add", "solutions/", "progress.json", "docs/"], cwd=str(BASE_DIR), check=True)
        status_res = subprocess.run(["git", "diff", "--staged", "--quiet"], cwd=str(BASE_DIR))
        if status_res.returncode == 0:
            return True
        subprocess.run(["git", "commit", "-m", commit_msg], cwd=str(BASE_DIR), check=True)
        push_res = subprocess.run(
            ["git", "push", "origin", "main"],
            cwd=str(BASE_DIR),
            capture_output=True,
            text=True
        )
        return push_res.returncode == 0
    except Exception as e:
        print(f"[Telegram] Git commit/push error: {e}")
        return False


def send_telegram_message(
    text: str,
    chat_id: Optional[str] = None,
    parse_mode: str = "HTML",
    reply_markup: Optional[Dict] = None
) -> bool:
    target_id = chat_id or TELEGRAM_CHAT_ID
    if not TELEGRAM_BOT_TOKEN or not target_id:
        return False

    payload = {
        "chat_id": target_id,
        "text": text,
        "parse_mode": parse_mode
    }
    if reply_markup:
        payload["reply_markup"] = reply_markup

    try:
        resp = requests.post(f"{API_BASE}/sendMessage", json=payload, timeout=20)
        if resp.status_code != 200 and parse_mode:
            # Fallback to plain text if HTML entity parsing failed
            payload.pop("parse_mode", None)
            resp = requests.post(f"{API_BASE}/sendMessage", json=payload, timeout=20)
        return resp.status_code == 200
    except Exception as e:
        print(f"[Telegram] Send message error: {e}")
        return False


def get_keyboard():
    return {
        "keyboard": [
            [{"text": "🚀 Solve Next Problem"}, {"text": "📊 Progress Status"}],
            [{"text": "📚 NeetCode Topics"}, {"text": "🌐 Dashboard"}, {"text": "❓ Help"}]
        ],
        "resize_keyboard": True
    }


def send_full_problem_solution(res: Dict[str, Any], chat_id: Optional[str] = None):
    """
    Sends a comprehensive, educational explanation of how the problem was solved
    followed by the full C++ solution code to Telegram.
    """
    slug = res.get("slug", "")
    name = res.get("name", "Unknown Problem")
    cat = res.get("category", "General")
    verdict = res.get("status", "Accepted")
    file_path = res.get("saved_path")

    intuition = "Optimal DSA pattern applied."
    approach = "Step-by-step approach."
    time_c = "O(N)"
    space_c = "O(1)"
    code_body = ""

    if file_path and Path(file_path).exists():
        file_text = Path(file_path).read_text(encoding="utf-8")

        # Extract Intuition
        int_match = re.search(r'--- Intuition ---\s*\n\s*\*(.*?)(?=\s*\*\s*--- Approach|\*/)', file_text, re.DOTALL)
        if int_match:
            clean_lines = [line.strip().lstrip('*').strip() for line in int_match.group(1).split('\n') if line.strip()]
            intuition = "\n".join(clean_lines)

        # Extract Approach
        app_match = re.search(r'--- Approach ---\s*\n\s*\*(.*?)(?=\s*\*\s*--- Complexity|\*/)', file_text, re.DOTALL)
        if app_match:
            clean_lines = [line.strip().lstrip('*').strip() for line in app_match.group(1).split('\n') if line.strip()]
            approach = "\n".join(clean_lines)

        # Extract Complexity
        t_match = re.search(r'Time Complexity:\s*(.*)', file_text)
        s_match = re.search(r'Space Complexity:\s*(.*)', file_text)
        if t_match:
            time_c = t_match.group(1).strip()
        if s_match:
            space_c = s_match.group(1).strip()

        # Extract C++ Code
        code_match = re.search(r'(#include.*)', file_text, re.DOTALL)
        if code_match:
            code_body = code_match.group(1).strip()
        else:
            code_body = file_text

    # Escape HTML to prevent Telegram entity parsing errors
    esc_name = html.escape(str(name))
    esc_cat = html.escape(str(cat))
    esc_verdict = html.escape(str(verdict))
    esc_intuition = html.escape(intuition)
    esc_approach = html.escape(approach)
    esc_time_c = html.escape(time_c)
    esc_space_c = html.escape(space_c)

    # Message 1: How It Was Solved & Complexity Analysis
    explanation_msg = (
        f"🎯 <b>Problem Solved: {esc_name}</b>\n"
        f"📂 <b>Category:</b> {esc_cat}\n"
        f"🟢 <b>LeetCode Verdict:</b> {esc_verdict}\n\n"
        f"💡 <b>HOW IT WAS SOLVED (Intuition):</b>\n"
        f"{esc_intuition}\n\n"
        f"🪜 <b>STEP-BY-STEP APPROACH:</b>\n"
        f"{esc_approach}\n\n"
        f"⏱️ <b>Time Complexity:</b> <code>{esc_time_c}</code>\n"
        f"💾 <b>Space Complexity:</b> <code>{esc_space_c}</code>\n\n"
        f"🔗 <a href='https://leetcode.com/problems/{slug}/'>View on LeetCode</a>"
    )
    send_telegram_message(explanation_msg, chat_id=chat_id, reply_markup=get_keyboard())

    # Message 2: Complete C++ Code
    if code_body:
        if len(code_body) > 3800:
            code_body = code_body[:3800] + "\n// ... [truncated for Telegram]"

        esc_code = html.escape(code_body)
        code_msg = (
            f"💻 <b>C++ Solution for {esc_name}:</b>\n"
            f"<pre><code class='language-cpp'>{esc_code}</code></pre>"
        )
        send_telegram_message(code_msg, chat_id=chat_id, reply_markup=get_keyboard())


class TelegramBotService:
    def __init__(self):
        self.last_update_id = 0
        self.agent = LeetCodeAgent()
        self.roadmap = RoadmapManager()
        self.tracker = ProgressTracker()
        self.is_solving = False
        self.solve_lock = threading.Lock()

    def handle_start(self, chat_id: str, first_name: str):
        save_chat_id(str(chat_id))
        welcome_msg = (
            f"👋 <b>Welcome, {html.escape(first_name)}!</b>\n\n"
            f"I am your personal <b>LeetCode NeetCode 250 DSA Agent</b>.\n\n"
            f"🎯 <b>What I do:</b>\n"
            f"• Pick the next unsolved question topic-wise from the NeetCode 250 sheet\n"
            f"• Generate optimal C++ solutions with Big-O complexity analysis\n"
            f"• Submit live to your LeetCode profile\n"
            f"• Refresh your GitHub Pages live dashboard & push commits to GitHub\n\n"
            f"👇 <b>Tap a button below or send a command to start:</b>"
        )
        send_telegram_message(welcome_msg, chat_id=chat_id, reply_markup=get_keyboard())

    def handle_status(self, chat_id: str):
        solved_slugs = self.tracker.get_solved_slugs()
        stats = self.roadmap.get_stats(solved_slugs)
        total = stats["total_problems"]
        solved = stats["total_solved"]
        pct = stats["overall_percent"]

        # Find current active topic
        active_cat = "All Topics Completed!"
        cat_progress = ""
        for cat, data in stats["categories"].items():
            if data["solved"] < data["total"]:
                active_cat = cat
                cat_progress = f"{data['solved']}/{data['total']} solved ({data['percent']}%)"
                break

        recent = self.tracker.get_recent_solutions(limit=3)
        recent_text = ""
        for r in recent:
            recent_text += f"\n• <b>{html.escape(r.get('name', 'N/A'))}</b> ({r.get('difficulty')}) - <i>{r.get('status')}</i>"

        msg = (
            f"📊 <b>NeetCode 250 Master Progress</b>\n\n"
            f"🏆 Completed: <b>{solved} / {total}</b> ({pct}%)\n"
            f"⏳ Remaining: <b>{total - solved}</b>\n\n"
            f"🎯 <b>Current Active Topic:</b>\n"
            f"<b>{active_cat}</b>: {cat_progress}\n\n"
            f"🕒 <b>Recent Submissions:</b>{recent_text or ' None yet'}\n\n"
            f"🌐 <a href='{DASHBOARD_URL}'>Open Live Web Dashboard</a>"
        )
        send_telegram_message(msg, chat_id=chat_id, reply_markup=get_keyboard())

    def handle_dashboard(self, chat_id: str):
        msg = (
            f"🌐 <b>Live Project Dashboard</b>\n\n"
            f"View your live roadmap progression, solved problem modals, code, and CI/CD stats here:\n"
            f"👉 <a href='{DASHBOARD_URL}'>{DASHBOARD_URL}</a>"
        )
        send_telegram_message(msg, chat_id=chat_id, reply_markup=get_keyboard())

    def handle_topics(self, chat_id: str):
        solved_slugs = self.tracker.get_solved_slugs()
        categories = self.roadmap.get_all_categories()

        lines = ["📚 <b>NeetCode 250 Roadmap Topics:</b>\n"]
        for idx, cat in enumerate(categories, 1):
            probs = self.roadmap.get_problems_by_category(cat)
            solved_c = len([p for p in probs if p["leetcode_slug"] in solved_slugs])
            icon = "✅" if solved_c == len(probs) and len(probs) > 0 else ("⏳" if solved_c > 0 else "⬜")
            lines.append(f"{icon} {idx}. <b>{html.escape(cat)}</b> ({solved_c}/{len(probs)})")

        send_telegram_message("\n".join(lines), chat_id=chat_id, reply_markup=get_keyboard())

    def handle_solve(self, chat_id: str, count: int = 1):
        with self.solve_lock:
            if self.is_solving:
                send_telegram_message(
                    "⏳ <b>A problem is currently being solved and submitted!</b>\n"
                    "Please wait a moment for the current solution to arrive.",
                    chat_id=chat_id,
                    reply_markup=get_keyboard()
                )
                return
            self.is_solving = True

        def _solve_thread():
            try:
                send_telegram_message(
                    f"⚡ <i>Selecting next {count} problem(s) from NeetCode 250 & generating optimal C++ solution...</i>",
                    chat_id=chat_id
                )
                results = self.agent.run_solve_cycle(count=count)
                if not results:
                    send_telegram_message(
                        "🎉 <b>All 250 questions in the sheet have been solved!</b>",
                        chat_id=chat_id,
                        reply_markup=get_keyboard()
                    )
                    return

                # Send educational solution breakdown and C++ code
                for res in results:
                    send_full_problem_solution(res, chat_id=chat_id)

                # 1. Rebuild web dashboard data
                try:
                    build_data()
                except Exception as b_err:
                    print(f"[Telegram] Dashboard rebuild error: {b_err}")

                # 2. Git Commit & Push
                solved_names = ", ".join([r.get("name", "Problem") for r in results if r.get("success")])
                if not solved_names:
                    solved_names = results[0].get("name", "NeetCode Problem")
                commit_msg = f"Auto-solve: {solved_names} solved via Telegram & dashboard refresh"
                pushed = git_commit_and_push(commit_msg)

                # 3. Send Completion Confirmation
                confirm_msg = (
                    f"✅ <b>Solve Cycle Complete!</b>\n"
                    f"📦 {'Pushed to GitHub main branch' if pushed else 'Saved locally'}\n"
                    f"🌐 <a href='{DASHBOARD_URL}'>View Live Dashboard</a>"
                )
                send_telegram_message(confirm_msg, chat_id=chat_id, reply_markup=get_keyboard())

            except Exception as e:
                send_telegram_message(
                    f"❌ <b>Error solving question:</b> {html.escape(str(e))}",
                    chat_id=chat_id,
                    reply_markup=get_keyboard()
                )
            finally:
                with self.solve_lock:
                    self.is_solving = False

        thread = threading.Thread(target=_solve_thread, daemon=True)
        thread.start()

    def start_polling(self):
        print(f"[Telegram] Bot listener active. Connected to: https://t.me/leetcdebot")

        while True:
            try:
                resp = requests.get(
                    f"{API_BASE}/getUpdates",
                    params={"offset": self.last_update_id + 1, "timeout": 20},
                    timeout=25
                )
                if resp.status_code != 200:
                    time.sleep(2)
                    continue

                data = resp.json()
                updates = data.get("result", [])

                for update in updates:
                    self.last_update_id = update["update_id"]
                    msg = update.get("message", {})
                    chat = msg.get("chat", {})
                    chat_id = str(chat.get("id"))
                    text = msg.get("text", "").strip()
                    first_name = chat.get("first_name", "Coder")

                    if not text or not chat_id:
                        continue

                    # Auto-save chat_id
                    global TELEGRAM_CHAT_ID
                    if not TELEGRAM_CHAT_ID:
                        TELEGRAM_CHAT_ID = chat_id
                        save_chat_id(chat_id)

                    text_lower = text.lower()
                    if text_lower in ("/start", "start"):
                        self.handle_start(chat_id, first_name)
                    elif text_lower in ("/status", "status") or "progress status" in text_lower:
                        self.handle_status(chat_id)
                    elif text_lower in ("/dashboard", "dashboard") or "dashboard" in text_lower:
                        self.handle_dashboard(chat_id)
                    elif text_lower in ("/topics", "topics") or "neetcode topics" in text_lower:
                        self.handle_topics(chat_id)
                    elif text_lower.startswith("/solve") or "solve next problem" in text_lower:
                        parts = text.split()
                        count = 1
                        if len(parts) > 1 and parts[1].isdigit():
                            count = min(int(parts[1]), 5)
                        self.handle_solve(chat_id, count=count)
                    elif text_lower in ("/help", "help") or "help" in text_lower:
                        help_text = (
                            "🤖 <b>Available Bot Commands:</b>\n\n"
                            "🚀 /solve - Solve & submit the next topic question\n"
                            "🚀 /solve 3 - Solve & submit next 3 questions\n"
                            "📊 /status - View progress & streak\n"
                            "📚 /topics - View all 18 NeetCode topics\n"
                            "🌐 /dashboard - Get link to live web dashboard\n"
                            "❓ /help - Show this menu"
                        )
                        send_telegram_message(help_text, chat_id=chat_id, reply_markup=get_keyboard())
                    else:
                        send_telegram_message(
                            "Tap <b>🚀 Solve Next Problem</b>, <b>📊 Progress Status</b>, or <b>🌐 Dashboard</b> below!",
                            chat_id=chat_id,
                            reply_markup=get_keyboard()
                        )

            except Exception as e:
                time.sleep(3)


def acquire_single_instance_lock(port: int = 49250):
    import socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.bind(("127.0.0.1", port))
        s.listen(1)
        return s
    except socket.error:
        print("[Telegram] Another instance of Telegram Bot is already running. Exiting.")
        sys.exit(0)


if __name__ == "__main__":
    from config import LOGS_DIR
    LOGS_DIR.mkdir(parents=True, exist_ok=True)
    bot_log = LOGS_DIR / "telegram_bot.log"
    logging.basicConfig(
        filename=str(bot_log),
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S"
    )
    _lock_sock = acquire_single_instance_lock()
    bot = TelegramBotService()
    bot.start_polling()

