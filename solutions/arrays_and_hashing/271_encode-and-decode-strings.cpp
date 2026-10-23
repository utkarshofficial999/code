/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears inside the length representation. During decoding we can read the length, skip the separator, and extract exactly that many characters – guaranteeing a loss‑less round‑trip even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector, compute its length `len`.
 * * Append `len`, a delimiter `'/'`, and the string itself to the result.
 * * The final encoded string is the concatenation of all such blocks.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Locate the next `'/'` to obtain the length of the upcoming original string.
 * * Convert the substring before `'/'` to an integer `len`.
 * * The original string occupies the next `len` characters; extract it and store it in the answer vector.
 * * Move the cursor past the extracted block and repeat until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter `'/'` is never part of the numeric length, so the split point is unambiguous.
 * * Because we always read exactly `len` characters after the delimiter, any character (including `'/'`) inside the original strings is handled safely.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both for encoding and decoding).
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter between length and content
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
            // slashPos must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, safeguard

            // length substring [i, slashPos)
            size_t len = 0;
            // manual conversion to avoid extra string allocation
            for (size_t p = i; p < slashPos; ++p) {
                len = len * 10 + (s[p] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // move cursor to the next block
            i = start + len;
        }
        return result;
    }
};
