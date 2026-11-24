/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its exact length followed by a special separator. Knowing the length removes any ambiguity caused by characters that may also appear as separators inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector, append `len(str)`, a delimiter (we use `'#'`), and then `str` itself to the result string.
 * * Example: `"abc"` → `"3#abc"`.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'#'` to obtain the length `len`.
 * * Extract the next `len` characters as the original string and store it.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty.
 * * Empty encoded string → decoded vector is empty.
 * * Strings may contain any character (including `'#'`) because the length tells us exactly where each string ends.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_characters) – each character is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_characters) – the encoded string and the output vector together store all characters.
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
            // j now points to delimiter
            size_t len = stoull(s.substr(i, j - i)); // safe for large lengths
            i = j + 1; // move past '#'
            result.emplace_back(s.substr(i, len));
            i += len; // move to start of next length field
        }
        return result;
    }
};
