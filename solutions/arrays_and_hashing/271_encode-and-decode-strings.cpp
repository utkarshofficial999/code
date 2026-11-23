/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator (e.g., ‘#’). Knowing the length lets us read the exact number of characters for every original string, so any character (including ‘#’) inside the string is safely handled.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `t`, append `to_string(t.size())`, then a delimiter `'#'`, then the string itself to the result.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Append the recovered string to the answer vector and continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_chars) – the encoded string and the output vector together store all characters.
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
            encoded += '#';          // delimiter that separates length from data
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
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // safety: malformed input (should not happen in LeetCode tests)
            if (j == n) break;

            long long len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');
            }

            i = j + 1; // skip '#'
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
