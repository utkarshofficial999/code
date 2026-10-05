import time
import sys
import random
import logging
from datetime import datetime, timedelta

if sys.platform.startswith("win"):
    try:
        sys.stdout.reconfigure(encoding="utf-8")
        sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

from rich.console import Console
from rich.panel import Panel
from rich.table import Table
from apscheduler.schedulers.blocking import BlockingScheduler
from apscheduler.triggers.cron import CronTrigger

from config import (
    SCHEDULE_TIMES,
    QUESTIONS_PER_SCHEDULE_RUN,
    RANDOM_JITTER_MINUTES,
    LOGS_DIR
)
from agent import LeetCodeAgent

console = Console(force_terminal=True, legacy_windows=False)


# Configure persistent logging
log_file = LOGS_DIR / "scheduler.log"
logging.basicConfig(
    filename=str(log_file),
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

def scheduled_job_worker(slot_time: str):
    """Worker triggered at each scheduled time slot."""
    logger = logging.getLogger("Scheduler")
    
    # Calculate jitter if configured
    if RANDOM_JITTER_MINUTES > 0:
        jitter_secs = random.randint(0, RANDOM_JITTER_MINUTES * 60)
        logger.info(f"Slot {slot_time}: applying randomized jitter delay of {jitter_secs // 60}m {jitter_secs % 60}s...")
        console.print(f"\n[dim][Scheduler] Slot {slot_time}: jitter delay of {jitter_secs // 60}m before execution...[/dim]")
        time.sleep(jitter_secs)

    logger.info(f"Starting scheduled solve cycle for slot {slot_time}...")
    console.print(f"\n[bold green]⏰ Triggering Scheduled Solve Cycle for {slot_time} ({datetime.now().strftime('%Y-%m-%d %H:%M:%S')})[/bold green]")

    try:
        agent = LeetCodeAgent()
        results = agent.run_solve_cycle(count=QUESTIONS_PER_SCHEDULE_RUN)
        logger.info(f"Solve cycle completed: {results}")

        # Send full solution & description notification to phone via Telegram
        try:
            from telegram_bot import send_full_problem_solution, send_telegram_message
            send_telegram_message(f"⏰ <b>Scheduled Solve Triggered! ({slot_time})</b>")
            for r in results:
                send_full_problem_solution(r)
        except Exception as te:
            logger.warning(f"Telegram notification failed: {te}")


    except Exception as e:
        logger.error(f"Error during scheduled solve cycle: {e}", exc_info=True)
        console.print(f"[bold red]✗ Error in scheduled run: {e}[/bold red]")

class DaemonScheduler:
    def __init__(self):
        self.scheduler = BlockingScheduler()
        self.agent = LeetCodeAgent()

    def start(self, run_immediately: bool = False):
        # Start Telegram Bot listener in a background thread
        try:
            import threading
            from telegram_bot import TelegramBotService
            bot_service = TelegramBotService()
            bot_thread = threading.Thread(target=bot_service.start_polling, daemon=True)
            bot_thread.start()
            console.print("[bold cyan]📱 Telegram Bot Connected! Control from: https://t.me/leetcdebot[/bold cyan]")
        except Exception as e:
            console.print(f"[dim]Telegram Bot not started: {e}[/dim]")

        if run_immediately:
            console.print("[cyan]Executing immediate initial solve cycle before starting schedule...[/cyan]")
            self.agent.run_solve_cycle(count=QUESTIONS_PER_SCHEDULE_RUN)


        table = Table(title="📅 Configured 24-Hour Schedule Times", show_header=True, header_style="bold magenta")
        table.add_column("Slot", style="cyan", width=8)
        table.add_column("Scheduled Time", style="yellow", width=18)
        table.add_column("DSA Questions/Run", style="green", width=20)
        table.add_column("Jitter Window", style="dim", width=18)

        for idx, t_str in enumerate(SCHEDULE_TIMES, 1):
            parts = t_str.split(":")
            if len(parts) != 2:
                continue
            hour, minute = int(parts[0]), int(parts[1])

            # Add Cron job to APScheduler
            self.scheduler.add_job(
                scheduled_job_worker,
                trigger=CronTrigger(hour=hour, minute=minute),
                args=[t_str],
                id=f"leetcode_slot_{idx}",
                name=f"LeetCode DSA Solve ({t_str})"
            )
            table.add_row(
                f"#{idx}",
                f"{hour:02d}:{minute:02d} Daily",
                f"{QUESTIONS_PER_SCHEDULE_RUN} question(s)",
                f"±{RANDOM_JITTER_MINUTES} mins"
            )

        console.print(table)
        console.print(Panel(
            f"[bold green]✓ LeetCode Agent Daemon is Active and Running[/bold green]\n"
            f"[dim]Tracking NeetCode 250 sheet topic-wise. Total 3 questions every 24 hours.[/dim]\n"
            f"[yellow]Press Ctrl+C at any time to pause or exit daemon.[/yellow]",
            title="[bold blue]Daemon Status[/bold blue]"
        ))

        try:
            self.scheduler.start()
        except (KeyboardInterrupt, SystemExit):
            console.print("\n[bold yellow]Scheduler stopped by user.[/bold yellow]")
