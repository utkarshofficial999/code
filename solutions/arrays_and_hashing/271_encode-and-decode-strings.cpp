/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length representation (e.g., ‘#’). During decoding we read the length, skip the separator, and extract exactly that many characters. This makes the process linear and immune to any characters that may appear inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a single character `'#'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each segment, read characters until `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations touch each character exactly once, guaranteeing linear time.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_characters) – each character of the input strings is written/read once.
 * Space Complexity: O(total_characters) – the encoded string stores all characters plus a small constant‑size overhead per original string.
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
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find the separator '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // length substring is s[i..j-1]
            size_t len = stoull(s.substr(i, j - i));
            // move past '#'
            i = j + 1;
            // extract the original string of length len
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
