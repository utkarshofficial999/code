/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘#’). Because the length tells us exactly how many characters belong to the original string, the separator can never be ambiguous even if the original string itself contains ‘#’.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `t`, append `to_string(t.size())`, then a single character `'#'`, then `t` itself to the result string.
 * * The concatenated result is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token, read characters until the separator `'#'` to obtain the length `len`.
 * * Convert `len` from string to integer, then take the next `len` characters as the original string.
 * * Append the recovered string to the answer vector and continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (both encode and decode).
 * Space Complexity: O(N) for the output string in encode and for the output vector in decode (aside from the input).
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
            encoded += '#';
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
            // j now points to '#'
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr);   // use unsigned long long to avoid overflow
            i = j + 1;                      // skip '#'

            // extract the original string of length len
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
