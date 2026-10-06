import os
from pathlib import Path
from dotenv import load_dotenv

# Load environment variables from .env file
BASE_DIR = Path(__file__).resolve().parent
ENV_PATH = BASE_DIR / ".env"
if ENV_PATH.exists():
    load_dotenv(dotenv_path=ENV_PATH)

# LeetCode Configuration
LEETCODE_SESSION = os.getenv("LEETCODE_SESSION", "").strip()
LEETCODE_CSRFTOKEN = os.getenv("LEETCODE_CSRFTOKEN", "").strip()

# AI / LLM Configuration
GEMINI_API_KEY = os.getenv("GEMINI_API_KEY", "").strip()
if GEMINI_API_KEY in ("your_gemini_api_key_here", "YOUR_GEMINI_API_KEY"):
    GEMINI_API_KEY = ""

GEMINI_MODEL = os.getenv("GEMINI_MODEL", "gemini-2.5-flash").strip()

GROQ_API_KEY = os.getenv("GROQ_API_KEY", "").strip()
GROQ_MODEL = os.getenv("GROQ_MODEL", "openai/gpt-oss-120b").strip()

OPENAI_API_KEY = os.getenv("OPENAI_API_KEY", "").strip()
if OPENAI_API_KEY in ("your_openai_api_key_here", "YOUR_OPENAI_API_KEY"):
    OPENAI_API_KEY = ""

OPENAI_BASE_URL = os.getenv("OPENAI_BASE_URL", "").strip()
OPENAI_MODEL = os.getenv("OPENAI_MODEL", "gpt-4o").strip()

# Telegram Bot Configuration
TELEGRAM_BOT_TOKEN = os.getenv("TELEGRAM_BOT_TOKEN", "").strip()
TELEGRAM_CHAT_ID = os.getenv("TELEGRAM_CHAT_ID", "").strip()



# Target Solution Language
SOLUTION_LANG = "cpp"
SOLUTION_LANG_SLUG = "cpp"

# Schedule Configuration
# 3 runs per day at different times (e.g. 09:00 morning, 15:45 afternoon, 16:15 evening)
SCHEDULE_TIMES_RAW = os.getenv("SCHEDULE_TIMES", "09:00,15:45,16:15")
SCHEDULE_TIMES = [t.strip() for t in SCHEDULE_TIMES_RAW.split(",") if t.strip()]

# How many questions to solve per scheduled trigger
# Default: 1 question at each of the 3 times = 3 questions every 24 hours
QUESTIONS_PER_SCHEDULE_RUN = int(os.getenv("QUESTIONS_PER_RUN", "1"))

# Random jitter in minutes (+/- jitter) to make submission times look natural
RANDOM_JITTER_MINUTES = int(os.getenv("RANDOM_JITTER_MINUTES", "15"))

# Storage Paths
DATA_FILE = BASE_DIR / "neetcode_250.json"
PROGRESS_FILE = BASE_DIR / "progress.json"
SOLUTIONS_DIR = BASE_DIR / "solutions"
LOGS_DIR = BASE_DIR / "logs"

SOLUTIONS_DIR.mkdir(parents=True, exist_ok=True)
LOGS_DIR.mkdir(parents=True, exist_ok=True)
