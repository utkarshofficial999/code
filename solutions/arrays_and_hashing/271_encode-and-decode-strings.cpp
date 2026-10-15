/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. While decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Initialise an empty result string `enc`.
 * * For every string `str` in the input vector:
 * – Append `to_string(str.size())` (the length).
 * – Append a special delimiter, e.g. `'#'`.
 * – Append the string `str` itself.
 * * Return the concatenated `enc`.
 * 
 * 2. **Decoding**
 * * Scan the encoded string `s` from left to right.
 * * For each token:
 * – Read characters until the delimiter `'#'` to obtain the length `len`.
 * – Convert the collected digits to an integer.
 * – Take the next `len` characters as the original string and push it into the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of `s`.
 * 
 * 3. The delimiter `'#'` is safe because it never appears in the numeric length part, and the length tells us exactly how many characters to read, so any `'#'` inside the original string is treated as ordinary data.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / vector (excluding the input).
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
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';               // delimiter
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr);   // length of the next string
            i = j + 1;                     // skip delimiter

            // extract the string of length 'len'
            decoded.emplace_back(s.substr(i, len));
            i += len;                      // move to start of next token
        }
        return decoded;
    }
};
