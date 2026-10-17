/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘#’). The separator guarantees that the decoder can unambiguously read the length, even when the original strings contain any characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a separator `'#'`, then `s` itself to the result string.
 * * The concatenated result is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the separator `'#'` to obtain the length `len` of the next original string.
 * * Convert `len` to an integer, then extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the decoded vector.
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
            encoded += '#';          // separator that never appears in the length field
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find separator '#'
            size_t sep = s.find('#', i);
            // safety check (should never happen for a valid encoding)
            if (sep == string::npos) break;
            // length of the next string
            size_t len = stoull(s.substr(i, sep - i));
            // extract the string
            size_t start = sep + 1;
            decoded.emplace_back(s.substr(start, len));
            // move index forward
            i = start + len;
        }
        return decoded;
    }
};
