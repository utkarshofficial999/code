/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’). Because the length tells us exactly where a string ends, the original content can contain any character (including the separator) without ambiguity. Decoding just reads the length, skips the separator, and extracts that many characters repeatedly.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to the result string.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Append the recovered string to the output vector and continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters in all strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields and delimiters).
 * Space Complexity: O(N) for the encoded string and the vector produced by decoding (the algorithm uses only a few extra variables).
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
            encoded += '/';          // delimiter that never appears in the length field
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t slashPos = s.find('/', i);
            // safety check – malformed input should not happen in LeetCode tests
            if (slashPos == string::npos) break;

            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1; // move past '/'

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
