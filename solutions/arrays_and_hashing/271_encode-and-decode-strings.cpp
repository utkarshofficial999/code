/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator (e.g., ‘/’).
 * Because the length is known, the decoder can unambiguously locate the next string even if the string itself contains the separator character.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, compute its length `len`.
 * * Append `len`, a separator `'/'`, and the string itself to the result.
 * * The final encoded string is the concatenation of all such blocks.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next separator `'/'` to obtain the length `len` of the upcoming string.
 * * Convert the substring before `'/'` to an integer, then read the next `len` characters as the original string.
 * * Advance the cursor past the processed block and repeat until the whole encoded string is consumed.
 * 
 * Both steps run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
            encoded += '/';          // separator that never appears in the length field
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find the separator that ends the length field
            size_t slashPos = s.find('/', i);
            // malformed input guard (should not happen in LeetCode tests)
            if (slashPos == string::npos) break;

            // extract length
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1; // move past '/'

            // extract the actual string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next block
        }
        return result;
    }
};
