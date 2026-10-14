/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each original string by prefixing it with its length and a special separator (e.g., ‘/’). The separator is never part of the length representation, so decoding can read the length, skip the separator, and extract exactly that many characters. This makes the process deterministic for any possible characters inside the strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'/'` is found – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Append the extracted string to the answer vector and continue from the position after those `len` characters.
 * * Stop when the whole encoded string has been processed.
 * 
 * Both steps run in linear time with respect to the total number of characters in all strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the extra digits for lengths and delimiters).
 * Space Complexity: O(N) for the output of encode and for the vector returned by decode (the algorithm itself uses only O(1) auxiliary space).
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
                         + strs.size() * 5 ); // rough reserve to avoid many reallocations
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // It must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, but we just stop
            // length substring
            size_t len = stoull(s.substr(i, slashPos - i));
            // extract the string of length 'len' after the delimiter
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));
            i = start + len;
        }
        return result;
    }
};
