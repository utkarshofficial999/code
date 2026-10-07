/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each original string by prefixing it with its length and a delimiter that never appears in the length representation (e.g., ‘:’). During decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, then a single delimiter `':'`, then the string itself to the result.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token, read characters until the delimiter `':'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are correctly encoded as `"0:"` and decoded back to `""`.
 * * Use `size_t` (64‑bit) for lengths to avoid overflow for very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(total number of characters) for both encode and decode.
 * Space Complexity: O(total number of characters) for the encoded string (output) and O(total number of characters) for the decoded vector (output). No extra auxiliary space beyond the outputs.
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
        // Reserve approximate size to avoid many reallocations.
        size_t total_len = 0;
        for (const auto& s : strs) total_len += s.size() + 20; // extra for length and delimiter
        encoded.reserve(total_len);

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += ':';          // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // Find delimiter ':'
            size_t delim = s.find(':', i);
            // If delimiter not found, the input is malformed; break.
            if (delim == string::npos) break;

            // Extract length substring and convert to integer
            size_t len = 0;
            // Manual conversion avoids extra string allocation
            for (size_t j = i; j < delim; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // Move cursor to the start of the actual string
            i = delim + 1;
            // Extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            // Advance cursor past the extracted string
            i += len;
        }
        return result;
    }
};
