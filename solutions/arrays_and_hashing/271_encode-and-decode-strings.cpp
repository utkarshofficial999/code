/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator (e.g., ‘/’). The length tells us exactly how many characters belong to the next original string, so any character (including the separator) can appear inside the original strings without ambiguity.
 *
 * --- Approach ---
 * 1. **Encode**
 * - For every string `str` in the input vector, append `len(str)`, a delimiter `'/'`, and then `str` itself to the result string.
 * - The concatenation of all such blocks forms the encoded representation.
 * 
 * 2. **Decode**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter `'/'`; the substring before it is the decimal length `L`.
 * - Convert `L` to an integer, then take the next `L` characters as the original string.
 * - Advance the pointer past those `L` characters and repeat until the whole encoded string is consumed.
 * 
 * 3. Use `size_t` / `uint64_t` for lengths to avoid overflow on very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(total number of characters) for both encoding and decoding.
 * Space Complexity: O(total number of characters) for the output (the encoded string or the decoded vector).
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
        encoded.reserve(strs.size() * 10); // small reservation, grows as needed
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter that separates length and string
            size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            uint64_t len = 0;
            // manual conversion avoids extra string allocation for huge inputs
            for (size_t p = i; p < slashPos; ++p) {
                len = len * 10 + (s[p] - '0');
            }
            i = slashPos + 1;               // move past '/'
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);   // skip the extracted string
        }
        return result;
    }
};
