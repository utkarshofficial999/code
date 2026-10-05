/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Valid Anagram (LeetCode #242)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/valid-anagram/
 * NeetCode URL: https://neetcode.io/problems/is-anagram?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 9.5 MB)
 *
 * --- Intuition ---
 * Two strings are anagrams iff they contain exactly the same multiset of characters. Because the input is limited to lowercase English letters, we can count occurrences of each letter in one pass and verify the counts against the second string.
 *
 * --- Approach ---
 * 1. If the lengths of `s` and `t` differ, return `false` immediately.
 * 2. Create a fixed‑size integer array `cnt[26]` initialized to zero.
 * 3. Iterate over `s`, increment `cnt[s[i]‑'a']`.
 * 4. Iterate over `t`, decrement the same counter.
 * 5. After processing both strings, if any entry in `cnt` is non‑zero the strings differ in character frequency → return `false`; otherwise return `true`.
 * 
 * *Follow‑up (Unicode)*: For arbitrary Unicode characters the fixed 26‑size array no longer works. Instead use an `unordered_map<char32_t,int>` (or `std::unordered_map<std::string,int>` after proper UTF‑8 decoding) to count frequencies, which still runs in linear time relative to the number of code points.
 *
 * --- Complexity ---
 * Time Complexity:  ** `O(n)` where `n = s.length()` (both strings are scanned once).
 * Space Complexity: ** `O(1)` – only a constant‑size array of 26 integers is used (or `O(k)` for `k` distinct Unicode code points in the follow‑up).
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

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        // Quick length check
        if (s.size() != t.size()) return false;

        // Frequency array for 26 lowercase letters
        array<int, 26> cnt{};
        cnt.fill(0);

        // Count characters in s
        for (char ch : s) {
            ++cnt[ch - 'a'];
        }

        // Subtract counts using t
        for (char ch : t) {
            if (--cnt[ch - 'a'] < 0) {
                // Early exit: more of this char in t than in s
                return false;
            }
        }

        // All counts must be zero; the early exit already guarantees this,
        // but we keep the check for completeness.
        for (int c : cnt) {
            if (c != 0) return false;
        }
        return true;
    }
};
