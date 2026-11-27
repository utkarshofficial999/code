/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each original string by prefixing it with its length and a special separator (e.g., ‘:’). Because the length tells us exactly where a string ends, the separator can appear inside the string without ambiguity. Decoding simply reads the length, skips the separator, and extracts that many characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `':'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token, read characters until the delimiter `':'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Append the extracted string to the answer vector and continue until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter is placed **after** the length, never inside the length field, so it can never be confused with characters belonging to the original strings.
 * * Using the exact length eliminates any dependence on the content of the original strings, handling empty strings, strings containing digits, colons, or any other ASCII/Unicode characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string in encode and for the resulting vector in decode.
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
            encoded += ':';               // delimiter separating length and content
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
            while (j < n && s[j] != ':') ++j;
            // j now points to the delimiter; substring [i, j) is the length
            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // move past ':'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next length field
        }
        return result;
    }
};
