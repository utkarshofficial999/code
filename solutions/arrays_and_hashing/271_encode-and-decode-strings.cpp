/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator.
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this makes the process unambiguous even when the original strings contain any possible characters (including the separator itself).
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Initialise an empty `std::string ans`.
 * * For every string `s` in the input vector:
 * - Append `std::to_string(s.size())`.
 * - Append a delimiter (choose a character that never appears in the length, e.g. `'#'`).
 * - Append the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decoding**
 * * Iterate over the encoded string with an index `i`.
 * * While `i` is less than the string length:
 * - Read characters until the delimiter `'#'` to obtain the length `len`.
 * - Convert the collected digits to an integer.
 * - Move `i` past the delimiter, then take the next `len` characters as one original string and push it into the answer vector.
 * - Advance `i` by `len` and repeat.
 * 
 * 3. The algorithm works for empty strings, empty vectors, and strings containing any characters (including the delimiter) because the delimiter is only used to separate the length from the payload, not inside the payload.
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
    // Encode a vector of strings to a single string.
    string encode(const vector<string>& strs) {
        const char SEP = '#';               // separator between length and string
        string encoded;
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(),
                                            (size_t)0,
                                            [](size_t sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve to avoid many reallocations

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += SEP;
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string back to a vector of strings.
    vector<string> decode(const string& s) {
        const char SEP = '#';
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t len = 0;
            while (i < n && s[i] != SEP) {
                // assuming only digits before separator
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            ++i; // skip the separator

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
