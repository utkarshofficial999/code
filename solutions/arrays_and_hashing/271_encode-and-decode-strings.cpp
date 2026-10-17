/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). Because the length tells us exactly how many characters belong to the original string, the separator can never be confused with the string’s content, even if the string itself contains ‘/’.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, append `to_string(str.size())`, then a single separator `'/'`, then the string itself to the result.
 * * The concatenated result is returned as the encoded single string.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next separator `'/'` to obtain the length `len` of the upcoming original string.
 * * Convert the substring before the separator to an integer, then read the next `len` characters as the original string.
 * * Append this string to the output vector and continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled naturally because their length is `0`.
 * * All characters (including the separator) are allowed inside the original strings because the length prefix disambiguates them.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output (encoded string or decoded vector).
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
            encoded += '/';          // separator
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& data) {
        vector<string> result;
        size_t i = 0, n = data.size();

        while (i < n) {
            // find separator '/'
            size_t slashPos = data.find('/', i);
            // It must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, stop

            // length of the next string
            size_t len = stoull(data.substr(i, slashPos - i));
            i = slashPos + 1; // move past '/'

            // extract the string of length len
            result.emplace_back(data.substr(i, len));
            i += len; // move to the start of the next length field
        }
        return result;
    }
};
