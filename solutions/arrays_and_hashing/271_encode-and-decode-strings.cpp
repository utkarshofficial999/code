/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length so that the decoder knows exactly where a string ends, regardless of the characters it contains. A simple “length + delimiter + string” format lets us reconstruct the original list in one linear pass.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, append `str.size()` followed by a special delimiter (e.g., `':'`) and then the string itself to a result `std::string`.
 * * Concatenating all such blocks yields the encoded representation.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `':'` to obtain the length `len` of the next original string.
 * * Extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is consumed.
 * 
 * 3. The delimiter `':'` is safe because the length field consists only of digits; any character (including `':'`) can appear inside the actual string part without ambiguity.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
        encoded.reserve(strs.size() * 10); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += ':';               // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != ':') ++j;
            // safety: malformed input (should not happen in LeetCode tests)
            if (j == n) break;
            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // skip ':'
            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
