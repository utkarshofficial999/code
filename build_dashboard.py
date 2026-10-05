import json
import re
from pathlib import Path
from datetime import datetime

BASE_DIR = Path(__file__).resolve().parent
PROGRESS_FILE = BASE_DIR / "progress.json"
DATA_FILE = BASE_DIR / "neetcode_250.json"
SOLUTIONS_DIR = BASE_DIR / "solutions"
DOCS_DIR = BASE_DIR / "docs"

def parse_cpp_file(file_path: Path):
    if not file_path.exists():
        return {}
    
    text = file_path.read_text(encoding="utf-8")
    
    intuition = ""
    approach = ""
    time_c = "O(N)"
    space_c = "O(1)"
    code_body = ""
    
    int_match = re.search(r'--- Intuition ---\s*\n\s*\*(.*?)(?=\s*\*\s*--- Approach|\*/)', text, re.DOTALL)
    if int_match:
        lines = [line.strip().lstrip('*').strip() for line in int_match.group(1).split('\n') if line.strip()]
        intuition = "\n".join(lines)
        
    app_match = re.search(r'--- Approach ---\s*\n\s*\*(.*?)(?=\s*\*\s*--- Complexity|\*/)', text, re.DOTALL)
    if app_match:
        lines = [line.strip().lstrip('*').strip() for line in app_match.group(1).split('\n') if line.strip()]
        approach = "\n".join(lines)
        
    t_match = re.search(r'Time Complexity:\s*(.*)', text)
    s_match = re.search(r'Space Complexity:\s*(.*)', text)
    if t_match:
        time_c = t_match.group(1).strip().replace('**', '').replace('`', '').strip()
    if s_match:
        space_c = s_match.group(1).strip().replace('**', '').replace('`', '').strip()
        
    code_match = re.search(r'(\*/\s*\n\s*#include.*)', text, re.DOTALL)
    if code_match:
        code_body = code_match.group(1).replace('*/\n', '').strip()
    else:
        # Fallback to after the first comment block
        parts = text.split('*/', 1)
        code_body = parts[1].strip() if len(parts) > 1 else text
        
    return {
        "intuition": intuition,
        "approach": approach,
        "time_complexity": time_c,
        "space_complexity": space_c,
        "code": code_body
    }

def build_data():
    DOCS_DIR.mkdir(parents=True, exist_ok=True)
    
    # 1. Load progress
    progress_data = {}
    if PROGRESS_FILE.exists():
        try:
            progress_data = json.loads(PROGRESS_FILE.read_text(encoding="utf-8"))
        except Exception:
            pass
            
    solved_dict = progress_data.get("solved", {})
    
    # 2. Load neetcode 250 master database
    nc_problems = []
    if DATA_FILE.exists():
        try:
            raw_nc = json.loads(DATA_FILE.read_text(encoding="utf-8"))
            if isinstance(raw_nc, dict):
                nc_problems = raw_nc.get("problems", [])
            elif isinstance(raw_nc, list):
                nc_problems = raw_nc
        except Exception as e:
            print(f"Error loading neetcode data: {e}")
            
    # Category aggregation
    categories_dict = {}
    slug_to_meta = {}
    
    for item in nc_problems:
        cat = item.get("category", "General")
        slug = item.get("leetcode_slug")
        slug_to_meta[slug] = item
        
        if cat not in categories_dict:
            categories_dict[cat] = {
                "name": cat,
                "total": 0,
                "solved": 0,
                "problems": []
            }
        categories_dict[cat]["total"] += 1
        is_solved = slug in solved_dict
        if is_solved:
            categories_dict[cat]["solved"] += 1
            
        categories_dict[cat]["problems"].append({
            "name": item.get("name"),
            "slug": slug,
            "difficulty": item.get("difficulty"),
            "solved": is_solved,
            "leetcode_url": f"https://leetcode.com/problems/{slug}/"
        })
        
    # List of solved problems with parsed code
    solved_list = []
    easy_count = 0
    med_count = 0
    hard_count = 0
    
    for slug, info in solved_dict.items():
        diff = info.get("difficulty", "Easy")
        if diff == "Easy":
            easy_count += 1
        elif diff == "Medium":
            med_count += 1
        elif diff == "Hard":
            hard_count += 1
            
        # Try finding solution file
        raw_path = info.get("solution_path", "")
        parsed_details = {}
        
        # Resolve path
        file_to_check = None
        if raw_path:
            p = Path(raw_path)
            if p.exists():
                file_to_check = p
            else:
                # Try finding in SOLUTIONS_DIR by filename
                candidate = SOLUTIONS_DIR / p.parent.name / p.name
                if candidate.exists():
                    file_to_check = candidate
                    
        if not file_to_check:
            # Search SOLUTIONS_DIR for this slug
            matches = list(SOLUTIONS_DIR.glob(f"**/*{slug}*.cpp"))
            if matches:
                file_to_check = matches[0]
                
        if file_to_check:
            parsed_details = parse_cpp_file(file_to_check)
            
        solved_list.append({
            "slug": slug,
            "name": info.get("name", slug),
            "category": info.get("category", "Arrays & Hashing"),
            "difficulty": diff,
            "solved_at": info.get("solved_at", ""),
            "status": info.get("status", "Accepted"),
            "runtime": info.get("runtime", "0 ms"),
            "memory": info.get("memory", "N/A"),
            "submission_id": info.get("submission_id"),
            "leetcode_url": f"https://leetcode.com/problems/{slug}/",
            "neetcode_url": f"https://neetcode.io/problems/{slug}?list=neetcode250",
            "intuition": parsed_details.get("intuition", "Optimal algorithm applied."),
            "approach": parsed_details.get("approach", "Step-by-step logic applied."),
            "time_complexity": parsed_details.get("time_complexity", "O(N)"),
            "space_complexity": parsed_details.get("space_complexity", "O(1)"),
            "code": parsed_details.get("code", "")
        })
        
    # Sort solved list newest first
    solved_list.sort(key=lambda x: x.get("solved_at", ""), reverse=True)
    
    total_problems = len(nc_problems) or 250
    total_solved = len(solved_list)
    overall_percent = round((total_solved / total_problems) * 100, 1) if total_problems else 0
    
    categories_list = []
    for cat_name, c_data in categories_dict.items():
        pct = round((c_data["solved"] / c_data["total"]) * 100, 1) if c_data["total"] else 0
        categories_list.append({
            "name": cat_name,
            "total": c_data["total"],
            "solved": c_data["solved"],
            "percent": pct,
            "problems": c_data["problems"]
        })
        
    summary = {
        "total_problems": total_problems,
        "total_solved": total_solved,
        "overall_percent": overall_percent,
        "easy_solved": easy_count,
        "medium_solved": med_count,
        "hard_solved": hard_count,
        "remaining": total_problems - total_solved,
        "last_updated": datetime.now().strftime("%Y-%m-%d %H:%M:%S IST")
    }
    
    output = {
        "summary": summary,
        "categories": categories_list,
        "solutions": solved_list
    }
    
    out_file = DOCS_DIR / "data.json"
    out_file.write_text(json.dumps(output, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"Generated dashboard data at {out_file} with {total_solved} solved solutions.")
    return output

if __name__ == "__main__":
    build_data()
