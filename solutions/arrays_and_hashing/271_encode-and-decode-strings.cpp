/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself. During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the process linear and works for any possible characters, including empty strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a special delimiter (e.g., `'#'`), and then `s` itself to the result string.
 * * The delimiter separates the length field from the actual data and cannot be confused with a digit because it is non‑numeric.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read consecutive digits to obtain the length `len`.
 * * Skip the delimiter `'#'`.
 * * Take the next `len` characters as one decoded string and push it into the answer vector.
 * * Continue until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty, decoding returns an empty vector.
 * * Empty strings inside the vector → encoded as `"0#"`; decoding correctly yields an empty string.
 * * Very long strings → length is parsed using `size_t` (via manual accumulation) to avoid overflow of `int`.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding (no extra auxiliary structures).
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
            encoded += '#';               // delimiter
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length (digits) until delimiter '#'
            size_t len = 0;
            while (i < n && isdigit(s[i])) {
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            // now s[i] must be '#'
            ++i; // skip delimiter

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
