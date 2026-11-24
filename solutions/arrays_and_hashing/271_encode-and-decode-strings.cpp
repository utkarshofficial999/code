/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’). The separator is safe because the length tells us exactly how many characters belong to the original string, so any character inside the string (including ‘/’) is handled correctly. Decoding just reads the length, skips the separator, and extracts that many characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `t`, append `to_string(t.size())`, then a delimiter `'/'`, then `t` itself to the result string.
 * * The delimiter separates the length field from the actual data; the length field guarantees correct parsing even if the data contains `'/'`.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each token, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the end of `s`.
 * 
 * 3. Return the encoded string from `encode` and the reconstructed vector from `decode`.
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter between length and data
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
            // safety: if not found, malformed input – break
            if (slashPos == string::npos) break;

            // length substring [i, slashPos)
            size_t len = 0;
            // manual conversion to avoid extra string allocation
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = slashPos + 1;
            string token = s.substr(start, len);
            result.push_back(std::move(token));

            // move cursor past the extracted token
            i = start + len;
        }
        return result;
    }
};
