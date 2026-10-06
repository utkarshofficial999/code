/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Sort Colors (LeetCode #075)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/sort-colors/
 * NeetCode URL: https://neetcode.io/problems/sort-colors?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 11.7 MB)
 *
 * --- Intuition ---
 * The array contains only three distinct values (0, 1, 2). By keeping three pointers that delimit the region of 0’s, 1’s and 2’s we can place each element into its correct region with a single left‑to‑right scan.
 *
 * --- Approach ---
 * 1. Initialise three indices:
 * * `low` – the first position that is not yet known to be a 0 (start of the “white” region).
 * * `mid` – the current element under inspection.
 * * `high` – the first position from the right that is not yet known to be a 2 (end of the “white” region).
 * Initially `low = mid = 0` and `high = n‑1`.
 * 2. While `mid <= high`
 * * If `nums[mid] == 0` → swap `nums[low]` and `nums[mid]`, then `++low` and `++mid`.
 * * Else if `nums[mid] == 1` → the element is already in the correct middle region, just `++mid`.
 * * Else (`nums[mid] == 2`) → swap `nums[mid]` and `nums[high]`, then `--high`.
 * *Do **not** increment `mid` here because the element swapped from `high` has not been examined yet.*
 * 3. When the loop finishes, all 0’s are before `low`, all 1’s between `low` and `high`, and all 2’s after `high`. The array is sorted in‑place.
 *
 * --- Complexity ---
 * Time Complexity:  O(n) – each element is examined at most once.
 * Space Complexity: O(1) – only a few integer indices are used.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

#include <vector>
#include <algorithm> // for std::swap (optional, can use manual swap)

class Solution {
public:
    void sortColors(std::vector<int>& nums) {
        // Edge case: empty or single‑element vector is already sorted
        if (nums.size() <= 1) return;

        int low = 0;                     // boundary for 0's
        int mid = 0;                     // current element
        int high = static_cast<int>(nums.size()) - 1; // boundary for 2's

        while (mid <= high) {
            switch (nums[mid]) {
                case 0:
                    std::swap(nums[low], nums[mid]);
                    ++low;
                    ++mid;
                    break;
                case 1:
                    ++mid;
                    break;
                case 2:
                    std::swap(nums[mid], nums[high]);
                    --high;
                    // do NOT increment mid here
                    break;
                default:
                    // Defensive programming: the problem guarantees only 0,1,2,
                    // but if an unexpected value appears we can treat it as 1.
                    ++mid;
                    break;
            }
        }
    }
};
