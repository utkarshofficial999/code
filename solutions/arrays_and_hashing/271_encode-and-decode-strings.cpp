/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). Because the length is a decimal number, the separator will never appear inside the length field, guaranteeing an unambiguous decoding even when the original strings contain any characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to a result string.
 * - Return the concatenated result.
 * 
 * 2. **Decode**
 * - Scan the encoded string from left to right.
 * - For each segment, read characters until the delimiter `'/'` to obtain the length `len`.
 * - Convert the length substring to an integer.
 * - Extract the next `len` characters as the original string and push it into the answer vector.
 * - Continue until the whole encoded string is processed.
 * 
 * Both steps run in linear time relative to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_chars) – the encoded string and the output vector together store all characters.
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
        size_t total_len = 0;
        for (const auto& s : strs) total_len += s.size() + 12; // extra for length and delimiter
        encoded.reserve(total_len);

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter that never appears in the length field
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // Find delimiter '/'
            size_t slashPos = s.find('/', i);
            // Defensive check – malformed input (should not happen in LeetCode)
            if (slashPos == string::npos) break;

            // Extract length
            size_t len = 0;
            // Manual conversion to avoid stoi overhead and handle large lengths safely
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // Extract the actual string of length 'len'
            size_t start = slashPos + 1;
            string token = s.substr(start, len);
            result.push_back(std::move(token));

            // Move index past the processed token
            i = start + len;
        }
        return result;
    }
};
