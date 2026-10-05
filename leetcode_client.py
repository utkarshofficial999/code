import re
import time
import requests
from typing import Dict, Any, Optional
from config import LEETCODE_SESSION, LEETCODE_CSRFTOKEN

GRAPHQL_URL = "https://leetcode.com/graphql"
BASE_HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36",
    "Accept": "*/*",
    "Referer": "https://leetcode.com",
    "Origin": "https://leetcode.com"
}

def clean_html(raw_html: str) -> str:
    """Converts LeetCode HTML content to clean readable markdown."""
    if not raw_html:
        return ""
    text = raw_html
    # Replace basic tags
    text = re.sub(r'</?(?:strong|b)>', '**', text)
    text = re.sub(r'</?(?:em|i)>', '*', text)
    text = re.sub(r'<code>(.*?)</code>', r'`\1`', text)
    text = re.sub(r'<pre>(.*?)</pre>', r'```\n\1\n```', text, flags=re.DOTALL)
    text = re.sub(r'<p>', '\n\n', text)
    text = re.sub(r'</p>', '', text)
    text = re.sub(r'<li>', '\n- ', text)
    text = re.sub(r'</li>', '', text)
    text = re.sub(r'<[^>]+>', '', text)
    # Decode entities
    text = text.replace('&nbsp;', ' ')
    text = text.replace('&lt;', '<')
    text = text.replace('&gt;', '>')
    text = text.replace('&quot;', '"')
    text = text.replace('&#39;', "'")
    text = text.replace('&amp;', '&')
    text = re.sub(r'\n{3,}', '\n\n', text)
    return text.strip()

class LeetCodeClient:
    def __init__(self, session: Optional[str] = None, csrftoken: Optional[str] = None):
        self.session = session if session is not None else LEETCODE_SESSION
        self.csrftoken = csrftoken if csrftoken is not None else LEETCODE_CSRFTOKEN
        self.req_session = requests.Session()
        self._update_headers()

    def _update_headers(self):
        headers = dict(BASE_HEADERS)
        if self.csrftoken:
            headers["x-csrftoken"] = self.csrftoken
        if self.session or self.csrftoken:
            cookies = []
            if self.session:
                cookies.append(f"LEETCODE_SESSION={self.session}")
            if self.csrftoken:
                cookies.append(f"csrftoken={self.csrftoken}")
            headers["Cookie"] = "; ".join(cookies)
        self.req_session.headers.update(headers)

    def is_authenticated(self) -> bool:
        return bool(self.session and self.csrftoken)

    def check_user_status(self) -> Dict[str, Any]:
        """Validates whether current cookies give a logged-in session on LeetCode."""
        query = """
        query userStatus {
            userStatus {
                isSignedIn
                username
                realName
                isPremium
            }
        }
        """
        try:
            resp = self.req_session.post(GRAPHQL_URL, json={"query": query}, timeout=10)
            if resp.status_code == 200:
                data = resp.json().get("data", {}).get("userStatus", {})
                return {
                    "is_signed_in": data.get("isSignedIn", False),
                    "username": data.get("username", "Anonymous"),
                    "is_premium": data.get("isPremium", False)
                }
            return {"is_signed_in": False, "error": f"HTTP {resp.status_code}"}
        except Exception as e:
            return {"is_signed_in": False, "error": str(e)}

    def fetch_question(self, title_slug: str) -> Optional[Dict[str, Any]]:
        """Fetches full question details including C++ starter snippet."""
        query = """
        query getQuestionDetail($titleSlug: String!) {
            question(titleSlug: $titleSlug) {
                questionId
                questionFrontendId
                title
                titleSlug
                content
                difficulty
                hints
                sampleTestCase
                codeSnippets {
                    lang
                    langSlug
                    code
                }
                topicTags {
                    name
                    slug
                }
            }
        }
        """
        try:
            resp = self.req_session.post(
                GRAPHQL_URL,
                json={"query": query, "variables": {"titleSlug": title_slug}},
                timeout=12
            )
            if resp.status_code != 200:
                print(f"[LeetCodeClient] Error fetching {title_slug}: HTTP {resp.status_code}")
                return None
            data = resp.json()
            q = data.get("data", {}).get("question")
            if not q:
                return None

            cpp_snippet = None
            snippets = q.get("codeSnippets", []) or []
            for s in snippets:
                if s["langSlug"] == "cpp":
                    cpp_snippet = s["code"]
                    break

            return {
                "question_id": q["questionId"],
                "frontend_id": q["questionFrontendId"],
                "title": q["title"],
                "slug": q["titleSlug"],
                "difficulty": q["difficulty"],
                "raw_content": q["content"],
                "clean_content": clean_html(q["content"]),
                "cpp_starter": cpp_snippet or "class Solution {\npublic:\n    // write code here\n};",
                "sample_testcase": q.get("sampleTestCase", ""),
                "hints": q.get("hints", []) or [],
                "topics": [t["name"] for t in q.get("topicTags", []) if "name" in t]
            }
        except Exception as e:
            print(f"[LeetCodeClient] Exception fetching {title_slug}: {e}")
            return None

    def submit_solution(self, title_slug: str, question_id: str, code: str) -> Dict[str, Any]:
        """
        Submits code to LeetCode and polls the submission status until finished.
        Returns full verdict and execution metrics.
        """
        if not self.is_authenticated():
            return {
                "success": False,
                "status_msg": "Not Authenticated",
                "simulated": True,
                "note": "LEETCODE_SESSION and LEETCODE_CSRFTOKEN are not set in .env. Solution saved locally."
            }

        submit_url = f"https://leetcode.com/problems/{title_slug}/submit/"
        payload = {
            "lang": "cpp",
            "question_id": str(question_id),
            "typed_code": code
        }

        submit_headers = dict(self.req_session.headers)
        submit_headers["Referer"] = f"https://leetcode.com/problems/{title_slug}/"

        try:
            resp = self.req_session.post(submit_url, json=payload, headers=submit_headers, timeout=15)
            if resp.status_code != 200:
                return {
                    "success": False,
                    "status_msg": f"Submission Failed (HTTP {resp.status_code})",
                    "details": resp.text[:300]
                }
            
            res_data = resp.json()
            submission_id = res_data.get("submission_id")
            if not submission_id:
                return {
                    "success": False,
                    "status_msg": "Submission Error",
                    "details": str(res_data)
                }

            # Poll submission status
            check_url = f"https://leetcode.com/submissions/detail/{submission_id}/check/"
            max_attempts = 20
            poll_interval = 1.0

            for _ in range(max_attempts):
                time.sleep(poll_interval)
                check_resp = self.req_session.get(check_url, headers=submit_headers, timeout=10)
                if check_resp.status_code != 200:
                    continue
                result = check_resp.json()
                state = result.get("state")

                if state == "SUCCESS":
                    status_code = result.get("status_code")
                    status_msg = result.get("status_msg") # e.g. "Accepted", "Compile Error", "Wrong Answer"
                    is_accepted = (status_msg == "Accepted" or status_code == 10)
                    
                    return {
                        "success": is_accepted,
                        "submission_id": submission_id,
                        "status_code": status_code,
                        "status_msg": status_msg,
                        "status_runtime": result.get("status_runtime", "N/A"),
                        "status_memory": result.get("status_memory", "N/A"),
                        "total_correct": result.get("total_correct", 0),
                        "total_testcases": result.get("total_testcases", 0),
                        "runtime_percentile": result.get("runtime_percentile"),
                        "memory_percentile": result.get("memory_percentile"),
                        "compile_error": result.get("compile_error"),
                        "last_testcase": result.get("last_testcase"),
                        "expected_output": result.get("expected_output"),
                        "code_output": result.get("code_output")
                    }

            return {
                "success": False,
                "submission_id": submission_id,
                "status_msg": "Timeout polling submission result"
            }

        except Exception as e:
            return {
                "success": False,
                "status_msg": f"Exception during submission: {e}"
            }
