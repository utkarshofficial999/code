/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘:’). The decoder can read the length, skip the separator, and extract exactly that many characters, guaranteeing correct reconstruction even if the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `':'`, then the string itself to the result.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `':'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both steps run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the decoded vector (output space).
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
        for (const auto& s : strs) total_len += s.size() + 10; // extra for length and ':'
        encoded.reserve(total_len);

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += ':';          // delimiter that never appears in the length field
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
            // Defensive check – malformed input should not happen in LeetCode tests.
            if (delim == string::npos) break;

            // Extract length
            size_t len = 0;
            // Manual conversion avoids overflow and is faster than stoi for huge inputs.
            for (size_t j = i; j < delim; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // Extract the string of length 'len'
            size_t start = delim + 1;
            result.emplace_back(s.substr(start, len));

            // Move index to the start of the next encoded block
            i = start + len;
        }
        return result;
    }
};
