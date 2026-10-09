/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). Because the length tells us exactly how many characters belong to the original string, the separator can never be ambiguous, even if the string itself contains ‘/’. Decoding simply reads the length, skips the separator, and extracts that many characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each token, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the end of the encoded string.
 * 
 * 3. The delimiter `'/'` is safe because the length field tells us exactly where the delimiter ends; the actual string may contain any characters, including `'/'`.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string (encoding) or the output vector of strings (decoding).
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
        // Reserve approximate size to avoid many reallocations
        size_t total = 0;
        for (const auto& s : strs) total += s.size() + 10; // extra for length and delimiter
        encoded.reserve(total);

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0;
        const size_t n = s.size();

        while (i < n) {
            // Find delimiter to extract length
            size_t slashPos = s.find('/', i);
            // Defensive check – malformed input should not happen in LeetCode tests
            if (slashPos == string::npos) break;

            // Parse length
            size_t len = 0;
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // Extract the original string
            size_t start = slashPos + 1;
            string token = s.substr(start, len);
            result.push_back(std::move(token));

            // Move index past the extracted token
            i = start + len;
        }
        return result;
    }
};
