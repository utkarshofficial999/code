/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator that never appears in the length representation. During decoding we read the length, skip the separator, and extract exactly that many characters. This makes the process independent of the string contents (including any possible delimiter characters).
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter character (e.g., `'#'`), then the string itself to the result.
 * * The delimiter is chosen because it never occurs in the numeric length representation, guaranteeing an unambiguous split.
 * 
 * 2. **Decoding**
 * * Scan the encoded string `s` from left to right.
 * * Locate the next delimiter `'#'` to obtain the substring representing the length. Convert it to an integer `len`.
 * * The actual string starts right after the delimiter and spans `len` characters. Append this substring to the output vector.
 * * Move the cursor past the extracted string and repeat until the end of `s`.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode returns an empty vector.
 * * Empty strings inside the vector are handled naturally because their length is `0`.
 * * All characters (including `'#'`) may appear inside the original strings; they are never confused with the delimiter because the delimiter is read **after** the length field.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the encoded string and the resulting vector of strings.
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
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';               // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '#'
            size_t delimPos = s.find('#', i);
            // safety check – malformed input would cause delimPos == string::npos
            if (delimPos == string::npos) break;

            // length substring [i, delimPos)
            size_t len = stoull(s.substr(i, delimPos - i));
            i = delimPos + 1; // move past '#'

            // extract the actual string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next encoded block
        }
        return result;
    }
};
