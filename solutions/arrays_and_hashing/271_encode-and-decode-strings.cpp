/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter.
 * During decoding we first read the length (stopping at the delimiter), then extract exactly that many characters – this works for any possible characters inside the original strings, including the delimiter itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `s` in the input vector, append `to_string(s.size())`, a special delimiter `'/'`, and then `s` itself to the result string.
 * * The delimiter is chosen only to separate the length from the payload; the payload can contain any character because we never rely on it for parsing.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length of the next original string.
 * * Convert the length substring to an integer (using a manual parser to avoid overflow).
 * * Extract the next `len` characters as the original string, push it into the answer vector, and continue from the position after those characters.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty.
 * * Empty strings inside the vector → encoded as `"0/"` and correctly decoded to `""`.
 * * Very long strings → length is stored as decimal digits; parsing uses `size_t` which can hold the full length on 64‑bit platforms.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the extra digits for lengths).
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
            encoded += '/';          // delimiter between length and string
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // parse length
            size_t len = 0;
            while (i < n && s[i] != '/') {
                // digit character guaranteed by encode
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            ++i; // skip the delimiter '/'

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
