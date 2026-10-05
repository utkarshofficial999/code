/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Group Anagrams (LeetCode #049)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/group-anagrams/
 * NeetCode URL: https://neetcode.io/problems/anagram-groups?list=neetcode250
 * Status: Accepted (Runtime: 35 ms, Memory: 28.2 MB)
 *
 * --- Intuition ---
 * Two strings are anagrams iff they contain exactly the same multiset of characters.
 * If we transform every string into a canonical representation that is identical for all its anagrams, we can simply bucket strings by that representation.
 *
 * --- Approach ---
 * 1. **Canonical key** – For each string count the occurrences of the 26 lower‑case letters (O(L) where *L* is the string length).
 * Encode the 26 counts into a single string, e.g. `"2#0#1#…"`; this key is identical for all anagrams.
 * 2. **Hash map** – Use an `unordered_map<string, vector<string>>` where the key is the encoded count and the value is the list of original strings that share this key.
 * 3. **Collect result** – Iterate over the map and move each vector into the final `vector<vector<string>>` to be returned.
 *
 * --- Complexity ---
 * Time Complexity:  **
 * Space Complexity: **
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
#include <unordered_map>

class Solution {
public:
    // Helper: convert a string into a 26‑letter frequency signature
    static std::string encode(const std::string& s) {
        int cnt[26] = {0};
        for (char c : s) ++cnt[c - 'a'];
        // Build a compact key; using a char buffer is faster than to_string repeatedly
        std::string key;
        key.reserve(52);               // 26 numbers + 26 separators
        for (int i = 0; i < 26; ++i) {
            key.append(std::to_string(cnt[i]));
            key.push_back('#');        // separator to avoid ambiguity (e.g. 11 vs 1|1)
        }
        return key;
    }

    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        groups.reserve(strs.size() * 2);   // reduce rehashes

        for (const std::string& s : strs) {
            std::string key = encode(s);
            groups[key].push_back(s);
        }

        std::vector<std::vector<std::string>> ans;
        ans.reserve(groups.size());
        for (auto& kv : groups) {
            ans.emplace_back(std::move(kv.second));
        }
        return ans;
    }
};
