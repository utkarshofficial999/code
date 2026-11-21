/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a non‑numeric separator.
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Iterate over the input vector `strs`.
 * - For each string `s` append `to_string(s.size())`, a delimiter (e.g., `':'`), and then `s` itself to the result string.
 * - The delimiter is chosen to be a character that never appears in the numeric length, so the boundary is unambiguous.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Read digits until the delimiter `':'` is met – this gives the length `len` of the next original string.
 * - Convert the digit sequence to an integer (`size_t`).
 * - Extract the next `len` characters as the original string and push it into the answer vector.
 * - Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encoded string is empty; decoding an empty string yields an empty vector.
 * - Strings may contain any characters, including the delimiter, because the delimiter is only used after the length field, not inside the string body.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the output).
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                              [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += ':';               // delimiter
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
            size_t len = 0;
            while (i < n && isdigit(s[i])) {
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            // skip delimiter ':'
            ++i; // we assume the format is always correct
            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
