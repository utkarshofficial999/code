# 🚀 LeetCode NeetCode 250 DSA Agent (C++)

An automated, intelligent LeetCode solving agent tailored for the **NeetCode 250** curriculum. It automatically tracks your DSA roadmap, solves 3 topic-wise questions every 24 hours across different times of the day in modern C++, tests & submits directly to your LeetCode profile, and archives production-ready code with time & space complexity analysis.

---

## ✨ Features

- **NeetCode 250 Roadmap Master**: Covers all 250 problems across 18 canonical DSA topics in sequential order (Arrays & Hashing, Two Pointers, Sliding Window, Trees, Graphs, DP, etc.).
- **24-Hour Multi-Time Scheduling**: Solves 3 questions per day distributed across customizable time slots (default: **9:00 AM**, **3:00 PM**, **9:00 PM**) with realistic randomized jitter (+/- 15 mins).
- **Modern C++ Solutions**: Writes clean, optimized C++17/20 code with standard STL headers, intuition, approach, and Big-$O$ time & space complexities.
- **LeetCode GraphQL & Submission Engine**: Fetches official problem statements and class templates; authenticates via session cookies and submits solutions directly to your LeetCode account.
- **Self-Healing Error Correction**: If LeetCode returns a *Wrong Answer* or *Compile Error*, the agent captures the failed test case and prompts the LLM to inspect, fix, and resubmit automatically (up to 3 attempts).
- **Persistent Progress Tracking**: Tracks solved problems in `progress.json`, preventing duplicates and displaying rich terminal status tables.
- **Local DSA Archive**: Saves formatted C++ files organized by topic in `solutions/<topic>/<id>_<slug>.cpp`.

---

## 📂 Project Structure

```
leetcode-agent/
│
├── .env.example          # Environment variable template
├── .env                  # Your private API keys & LeetCode cookies
├── config.py             # Agent configuration loader
├── neetcode_250.json     # Master database of 250 NeetCode questions
├── leetcode_client.py    # LeetCode GraphQL fetch & submission API
├── solver.py             # LLM prompt engineer & C++ solution generator
├── solution_saver.py     # Local C++ file formatter and organizer
├── roadmap.py            # NeetCode 250 progression & topic manager
├── tracker.py            # Local progress & history database (progress.json)
├── scheduler.py          # APScheduler 24-hr multi-time daemon with jitter
├── main.py               # Main CLI interface & dashboard
├── requirements.txt      # Python dependencies
└── solutions/            # Directory where solved C++ files are saved
    ├── arrays_and_hashing/
    ├── two_pointers/
    └── ...
```

---

## 🛠️ Quickstart Guide

### 1. Set Up Environment

The virtual environment is already prepared at `.venv`. To activate it:

**Windows (PowerShell):**
```powershell
.\.venv\Scripts\Activate.ps1
```

**Windows (CMD):**
```cmd
.\.venv\Scripts\activate.bat
```

### 2. Configure Credentials in `.env`

Open `.env` and fill in your settings:

```env
# 1. Google Gemini API Key (Required for AI solving)
# Free key available at: https://aistudio.google.com/app/apikey
GEMINI_API_KEY=your_actual_gemini_api_key_here
GEMINI_MODEL=gemini-2.5-flash

# 2. LeetCode Session Cookies (For direct auto-submission to LeetCode)
# Login to https://leetcode.com -> Open DevTools (F12) -> Application -> Cookies -> https://leetcode.com
LEETCODE_SESSION=
LEETCODE_CSRFTOKEN=

# 3. Schedule Settings
SCHEDULE_TIMES=09:00,15:45,16:15
QUESTIONS_PER_RUN=1
RANDOM_JITTER_MINUTES=15
```

> **Note:** If `LEETCODE_SESSION` is not yet configured, the agent operates in **Local Practice Mode** — generating, validating, and saving C++ solutions locally without submitting to LeetCode.

---

## 💻 CLI Commands

### 1. Verify Credentials
```powershell
.\.venv\Scripts\python.exe main.py check-auth
```
Checks your Gemini API key and tests your live login status on LeetCode.

### 2. View Progress Dashboard
```powershell
.\.venv\Scripts\python.exe main.py status
```
Displays overall completion percentage, topic-by-topic progress bars, and recent submissions.

### 3. Solve Questions Immediately
```powershell
# Solve the next 3 topic-wise questions right now
.\.venv\Scripts\python.exe main.py solve -c 3

# Target a specific topic
.\.venv\Scripts\python.exe main.py solve -c 3 -t "Arrays & Hashing"
```

### 4. Start 24-Hour Multi-Time Daemon
```powershell
# Runs in the foreground/background terminal at 09:00, 15:45, 16:15
.\.venv\Scripts\python.exe main.py daemon

# Or start daemon and solve 1 cycle immediately
.\.venv\Scripts\python.exe main.py daemon --now
```

### 4b. Setup Windows Task Scheduler (Recommended - 100% Reliable & Silent)
```powershell
# Automatically register daily scheduled tasks from .env SCHEDULE_TIMES (09:00, 15:45, 16:15)
.\setup_scheduler.ps1 -Action Install

# View all active registered tasks
.\setup_scheduler.ps1 -Action List

# Trigger an immediate run anytime
.\setup_scheduler.ps1 -Action RunNow

# Remove tasks if needed
.\setup_scheduler.ps1 -Action Uninstall
```

### 5. View Roadmap Topics
```powershell
.\.venv\Scripts\python.exe main.py topics
```

### 6. Reset Tracking
```powershell
.\.venv\Scripts\python.exe main.py reset --confirm
```

---

## ⏱️ How the 24-Hour Multi-Time Daemon Works

1. The agent reads `SCHEDULE_TIMES` (e.g. `09:00,15:45,16:15`).
2. When a scheduled time arrives, it applies a random jitter (between 0 and `RANDOM_JITTER_MINUTES`) so requests do not trigger at the exact same millisecond every day.
3. It consults `roadmap.py` and `tracker.py` to pick the next unsolved question from the active NeetCode topic.
4. It fetches live question specifications and C++ starter boilerplate from LeetCode.
5. It crafts an optimal C++ solution with the configured LLM.
6. It submits the code to LeetCode and monitors the verdict.
7. If needed, it self-corrects using error diagnostic feedback.
8. It saves the final C++ code in `solutions/` and logs the completion in `progress.json`.
