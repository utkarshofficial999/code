/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). Because the length tells us exactly how many characters belong to the original string, the separator can appear anywhere inside the string without ambiguity.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector:
 * – Compute its length `len`.
 * – Append `len`, a delimiter `'/'`, and the string itself to the result.
 * * The concatenated result is returned as the encoded single string.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Read characters until the delimiter `'/'` to obtain the length `len`.
 * – Convert the extracted substring to an integer.
 * – The next `len` characters form the original string; push it into the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. The algorithm works for empty strings, strings containing any characters (including the delimiter), and very large inputs because the length prefix removes any ambiguity.
 *
 * --- Complexity ---
 * Time Complexity:  
 * Space Complexity: 
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), (size_t)0,
                                            [](size_t sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // It must exist in a valid encoding
            if (slashPos == string::npos) break;

            // length substring [i, slashPos)
            size_t len = 0;
            // manual conversion to avoid extra string allocation
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // move cursor past the extracted string
            i = start + len;
        }
        return result;
    }
};
