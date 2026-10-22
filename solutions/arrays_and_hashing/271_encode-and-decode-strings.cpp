/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears in the length itself. During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter (e.g., `'#'`), then `s` itself to the result string.
 * * The delimiter is safe because it never occurs in the decimal representation of the length.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * Locate the next delimiter `'#'` to obtain the length of the next original string.
 * * Convert the substring before `'#'` to an integer `len`.
 * * The original string starts right after the delimiter and spans `len` characters; extract it and push it into the answer vector.
 * * Move the scanning pointer past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode returns an empty vector.
 * * Empty strings inside the vector → length `0` is encoded as `"0#"` and decoded correctly.
 * * Very long strings or many strings → algorithm runs in linear time with respect to total characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / vector (aside from the input).
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
        for (const auto& s : strs) total_len += s.size() + 10; // extra for length and delimiter
        encoded.reserve(total_len);

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0;
        while (i < s.size()) {
            // Find delimiter '#'
            size_t delim = s.find('#', i);
            // Safety check – delimiter must exist
            if (delim == string::npos) break; // malformed input, but LeetCode guarantees well‑formed

            // Extract length
            size_t len = 0;
            // stoi can throw; we parse manually to avoid overhead
            for (size_t j = i; j < delim; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // Extract the original string
            size_t start = delim + 1;
            result.emplace_back(s.substr(start, len));

            // Move index past the extracted string
            i = start + len;
        }
        return result;
    }
};
