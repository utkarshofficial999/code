/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator (e.g., ‘#’).
 * During decoding we first read the length, skip the separator, then read exactly that many characters – the separator can appear inside the original string without causing ambiguity.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `str` in the input vector:
 * – Append `to_string(str.size())`, then a delimiter `'#'`, then the string itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Read characters until `'#'` to obtain the length `len`.
 * – Convert the collected digits to an integer.
 * – Extract the next `len` characters as the original string and push it into the answer vector.
 * – Continue from the position after those `len` characters.
 * * Return the reconstructed vector.
 * 
 * 3. The delimiter is never interpreted as part of the length; we always know exactly how many characters to read after it, so any character (including ‘#’) inside the original strings is safe.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is processed a constant number of times).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the result).
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
            size_t len = stoull(lenStr);   // length of the next string
            i = j + 1;                      // position of the first character of the string
            result.emplace_back(s.substr(i, len));
            i += len;                       // move to the start of the next length field
        }
        return result;
    }
};
