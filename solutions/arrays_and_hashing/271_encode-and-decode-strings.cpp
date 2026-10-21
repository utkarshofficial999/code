/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a unique separator.
 * During decoding we read the length, skip the separator and extract exactly that many characters – the original string is recovered even if it contains any possible character.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `s` in the input vector, compute `len = s.size()`.
 * * Append `len`, a delimiter (choose '`:`'), and the string itself to the result.
 * * The final encoded string is the concatenation of all such blocks.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`:`' – this gives the length `len`.
 * * Convert the collected digits to an integer.
 * * Take the next `len` characters as one original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input list → encode returns an empty string, decode returns an empty vector.
 * * Empty strings inside the list are handled because their length is `0` (`"0:"`).
 * * The delimiter is never part of the length field, so any character may appear inside the original strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encode and decode scan each character once).
 * Space Complexity: O(N) for the encoded string and the vector returned by decode.
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
            encoded += ':';               // delimiter between length and content
            encoded += s;                 // actual string (may be empty)
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != ':') ++j;
            // j now points to the delimiter
            long long len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');
            }
            i = j + 1; // move past ':'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
