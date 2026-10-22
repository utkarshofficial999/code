/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a unique separator (e.g., ‘/’).
 * During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `result` string.
 * * For every string `s` in the input vector:
 * – Append `to_string(s.size())`, then a separator `'/'`, then the string `s` itself.
 * * Return the concatenated `result`.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Locate the next `'/'` to obtain the length field.
 * – Convert the substring before `'/'` to an integer `len`.
 * – The next `len` characters form the original string; push it into the answer vector.
 * – Advance the cursor past the extracted string and repeat until the end.
 * 
 * 3. The separator `'/'` is safe because it never appears in the length field, and the length tells us exactly how many characters belong to the original string, regardless of its content.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string in encode and for the resulting vector in decode.
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
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find separator '/'
            size_t slashPos = s.find('/', i);
            // length field must exist
            if (slashPos == string::npos) break; // malformed input, but we stop gracefully

            // parse length
            size_t len = 0;
            // manual conversion to avoid extra string allocation
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the original string
            size_t start = slashPos + 1;
            decoded.emplace_back(s.substr(start, len));

            // move cursor forward
            i = start + len;
        }
        return decoded;
    }
};
