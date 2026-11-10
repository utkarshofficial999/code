/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator that never appears in the length representation. During decoding we read the length, skip the separator, and extract exactly that many characters. This makes the process deterministic and works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (e.g., `'#'`), and then `s` itself to the result string.
 * * The delimiter is chosen because it never occurs in the decimal representation of the length, guaranteeing an unambiguous split.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted string and repeat until the end of the encoded data.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (`"0#"`).
 * * Very long strings are processed using `size_t` to avoid overflow.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length delimiters).
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
            encoded += '#';          // delimiter
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
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter
            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // skip delimiter
            result.emplace_back(s.substr(i, len));
            i += len;  // move to next encoded block
        }
        return result;
    }
};
