/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. During decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, append `to_string(str.size())`, a single delimiter `'/'`, and then `str` itself to the result string.
 * * The delimiter is chosen because it never occurs in the decimal representation of the length.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length `len` of the next original string.
 * * Convert the substring before the delimiter to an integer.
 * * The original string occupies the next `len` characters; extract it and push it into the answer vector.
 * * Move the scanning pointer past the extracted part and repeat until the whole encoded string is processed.
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
            // It must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, safeguard

            // length of the next string
            size_t len = 0;
            // convert substring [i, slashPos) to integer
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the actual string
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // move i to the start of the next encoded block
            i = start + len;
        }
        return result;
    }
};
