import re
import os
import sys
import requests
from typing import Dict, Any, Optional, Tuple
if sys.platform.startswith("win"):
    try:
        sys.stdout.reconfigure(encoding="utf-8")
        sys.stderr.reconfigure(encoding="utf-8")
    except Exception:
        pass

from config import (
    GEMINI_API_KEY, GEMINI_MODEL,
    GROQ_API_KEY, GROQ_MODEL,
    OPENAI_API_KEY, OPENAI_BASE_URL, OPENAI_MODEL
)

class ProblemSolver:
    def __init__(self):
        self.gemini_client = None
        self.groq_key = None
        self.openai_client = None
        self.openai_key = None
        self._init_clients()

    def _init_clients(self):
        # 1. Initialize Groq if key is present
        groq_k = GROQ_API_KEY or os.getenv("GROQ_API_KEY")
        if groq_k:
            self.groq_key = groq_k
            self.groq_model = GROQ_MODEL or "openai/gpt-oss-120b"

        # 2. Initialize Google Gemini if key is present
        api_key = GEMINI_API_KEY or os.getenv("GEMINI_API_KEY")
        if api_key:
            try:
                from google import genai
                self.gemini_client = genai.Client(api_key=api_key)
            except Exception as e:
                print(f"[Solver] Note: Google GenAI client init failed: {e}")

        # 3. Initialize OpenAI if key is present
        openai_key = OPENAI_API_KEY or os.getenv("OPENAI_API_KEY")
        if openai_key:
            self.openai_key = openai_key
            self.openai_base_url = OPENAI_BASE_URL or "https://api.openai.com/v1"

    def is_configured(self) -> bool:
        return bool(self.groq_key or self.gemini_client or (OPENAI_API_KEY or os.getenv("OPENAI_API_KEY")))

    def _call_groq(self, prompt: str) -> str:
        headers = {
            "Authorization": f"Bearer {self.groq_key}",
            "Content-Type": "application/json"
        }
        payload = {
            "model": self.groq_model,
            "messages": [
                {"role": "system", "content": "You are a competitive programming world finalist and expert C++ software engineer."},
                {"role": "user", "content": prompt}
            ],
            "temperature": 0.2
        }
        resp = requests.post("https://api.groq.com/openai/v1/chat/completions", headers=headers, json=payload, timeout=45)
        if resp.status_code == 200:
            return resp.json()["choices"][0]["message"]["content"]
        raise RuntimeError(f"Groq API error {resp.status_code}: {resp.text}")

    def _call_gemini(self, prompt: str) -> str:
        if not self.gemini_client:
            raise RuntimeError("Gemini client not initialized")
        response = self.gemini_client.models.generate_content(
            model=GEMINI_MODEL,
            contents=prompt,
        )
        return response.text

    def _call_openai(self, prompt: str) -> str:
        headers = {
            "Authorization": f"Bearer {self.openai_key}",
            "Content-Type": "application/json"
        }
        payload = {
            "model": OPENAI_MODEL,
            "messages": [
                {"role": "system", "content": "You are a competitive programming world finalist and expert C++ software engineer."},
                {"role": "user", "content": prompt}
            ],
            "temperature": 0.2
        }
        resp = requests.post(f"{self.openai_base_url}/chat/completions", headers=headers, json=payload, timeout=45)
        if resp.status_code == 200:
            return resp.json()["choices"][0]["message"]["content"]
        raise RuntimeError(f"OpenAI API error {resp.status_code}: {resp.text}")

    def _generate_llm_text(self, prompt: str) -> str:
        errors = []
        if self.groq_key:
            try:
                return self._call_groq(prompt)
            except Exception as e:
                errors.append(f"Groq error: {e}")
                print(f"[Solver] Groq call failed: {e}. Trying fallback if available...")

        if self.gemini_client:
            try:
                return self._call_gemini(prompt)
            except Exception as e:
                errors.append(f"Gemini error: {e}")
                print(f"[Solver] Gemini call failed: {e}. Trying fallback if available...")

        if self.openai_key:
            try:
                return self._call_openai(prompt)
            except Exception as e:
                errors.append(f"OpenAI error: {e}")
                print(f"[Solver] OpenAI call failed: {e}.")

        if errors:
            raise RuntimeError(" | ".join(errors))
        raise RuntimeError("No LLM API key configured! Please set GROQ_API_KEY or GEMINI_API_KEY in .env")


    def solve(self, question: Dict[str, Any], previous_error: Optional[str] = None) -> Dict[str, Any]:
        """
        Solves the LeetCode DSA problem in optimal C++.
        If previous_error is provided (from a failed submission), the LLM self-corrects.
        """
        title = question.get("title", "")
        difficulty = question.get("difficulty", "")
        category = question.get("category", "")
        content = question.get("clean_content", "")
        starter_code = question.get("cpp_starter", "")
        sample_test = question.get("sample_testcase", "")

        error_context = ""
        if previous_error:
            error_context = f"""
IMPORTANT: A previous submission failed with this error / failed testcase:
{previous_error}

Analyze why the previous solution failed or timed out, and fix the edge case or optimize the algorithm.
"""

        prompt = f"""You are an elite competitive programmer and expert C++ developer solving a LeetCode problem from the NeetCode 250 sheet.

Problem Title: {title}
Category: {category}
Difficulty: {difficulty}

Problem Statement:
{content}

LeetCode C++ Starter Code Template:
```cpp
{starter_code}
```

Sample Testcase:
{sample_test}
{error_context}

REQUIREMENTS:
1. Write the complete, production-ready, highly optimal C++ solution.
2. Must match the exact class and function signatures from the starter code template.
3. Include standard library headers (#include <vector>, #include <unordered_map>, #include <algorithm>, etc.) before the class.
4. Aim for optimal Time Complexity and Space Complexity.
5. Handle all edge cases, extreme bounds, large inputs, negative values, and potential integer overflow.
6. Provide an Intuition section, an Approach section, and exact Big-O Time & Space Complexity analysis.

FORMAT YOUR RESPONSE EXACTLY AS FOLLOWS:

### INTUITION
(2-3 sentences explaining the key insight)

### APPROACH
1. (Step 1)
2. (Step 2)
...

### COMPLEXITY
- Time Complexity: O(...)
- Space Complexity: O(...)

### CODE
```cpp
// Full valid C++ solution here
```
"""

        try:
            raw_response = self._generate_llm_text(prompt)
            parsed = self._parse_response(raw_response, starter_code)
            return parsed
        except Exception as e:
            return {
                "success": False,
                "error": str(e),
                "code": starter_code,
                "intuition": "Error invoking LLM",
                "approach": "N/A",
                "time_complexity": "N/A",
                "space_complexity": "N/A",
                "raw_response": ""
            }

    def _parse_response(self, response_text: str, fallback_starter: str) -> Dict[str, Any]:
        # Extract C++ code
        code = ""
        code_match = re.search(r'```(?:cpp|c\+\+)?\s*(.*?)\s*```', response_text, re.DOTALL | re.IGNORECASE)
        if code_match:
            code = code_match.group(1).strip()
        else:
            # Fallback if no markdown codeblock
            code = fallback_starter

        # Extract Intuition
        intuition = "Optimal DSA solution."
        int_match = re.search(r'###\s*INTUITION\s*(.*?)(?=###|\Z)', response_text, re.DOTALL | re.IGNORECASE)
        if int_match:
            intuition = int_match.group(1).strip()

        # Extract Approach
        approach = ""
        app_match = re.search(r'###\s*APPROACH\s*(.*?)(?=###|\Z)', response_text, re.DOTALL | re.IGNORECASE)
        if app_match:
            approach = app_match.group(1).strip()

        # Extract Complexity
        time_comp = "O(N)"
        space_comp = "O(1)"
        comp_match = re.search(r'###\s*COMPLEXITY\s*(.*?)(?=###|\Z)', response_text, re.DOTALL | re.IGNORECASE)
        if comp_match:
            comp_text = comp_match.group(1)
            t_match = re.search(r'Time\s*Complexity:\s*(.*)', comp_text, re.IGNORECASE)
            s_match = re.search(r'Space\s*Complexity:\s*(.*)', comp_text, re.IGNORECASE)
            if t_match:
                time_comp = re.sub(r'[*`]', '', t_match.group(1)).strip()
            if s_match:
                space_comp = re.sub(r'[*`]', '', s_match.group(1)).strip()

        # Determine expected class or structure from fallback_starter
        expected_class = None
        class_match = re.search(r'\bclass\s+([A-Za-z0-9_]+)', fallback_starter)
        if class_match:
            expected_class = class_match.group(1)

        is_valid_code = bool(code and len(code.strip()) > 20)
        if expected_class:
            has_class_structure = (expected_class in code) or ("class " in code)
        else:
            has_class_structure = ("class " in code) or ("struct " in code) or ("using " in code)

        return {
            "success": bool(is_valid_code and has_class_structure),
            "code": code,
            "intuition": intuition,
            "approach": approach,
            "time_complexity": time_comp,
            "space_complexity": space_comp,
            "raw_response": response_text
        }
