/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Longest Common Prefix (LeetCode #014)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/longest-common-prefix/
 * NeetCode URL: https://neetcode.io/problems/longest-common-prefix?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 11.7 MB)
 *
 * --- Intuition ---
 * The common prefix can be at most as long as the shortest string in the array. By comparing characters column‑wise (i.e., the same index in every string) we can stop as soon as a mismatch or the end of the shortest string is reached.
 *
 * --- Approach ---
 * 1. **Find the minimum length** among all strings – the longest possible prefix cannot exceed this length.
 * 2. **Iterate index `i` from `0` to `minLen‑1`** and check the character at position `i` in every string.
 * 3. If all characters are identical, continue; otherwise the current index marks the end of the common prefix.
 * 4. Return the substring of any string (e.g., `strs[0]`) from `0` to the discovered length.
 *
 * --- Complexity ---
 * Time Complexity:  ** `O(N * L)` where `N` is the number of strings and `L` is the length of the shortest string (worst‑case total characters examined).
 * Space Complexity: ** `O(1)` extra space (ignoring the input and output).
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
#include <string>
#include <algorithm> // for min_element
#include <limits>    // for numeric_limits

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.empty()) return "";

        // 1. Find the length of the shortest string.
        std::size_t minLen = std::numeric_limits<std::size_t>::max();
        for (const auto& s : strs) {
            minLen = std::min(minLen, s.size());
        }

        // 2. Compare characters column‑wise.
        std::size_t prefixLen = 0;
        for (std::size_t i = 0; i < minLen; ++i) {
            char cur = strs[0][i];
            bool allMatch = true;
            for (std::size_t j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != cur) {
                    allMatch = false;
                    break;
                }
            }
            if (!allMatch) break;
            ++prefixLen;
        }

        // 3. Return the common prefix.
        return strs[0].substr(0, prefixLen);
    }
};
