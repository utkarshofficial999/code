/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’). Because the length is written in decimal, the separator never appears inside the numeric prefix, guaranteeing an unambiguous boundary. Decoding simply reads the length, skips the separator, and extracts that many characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Append the extracted string to the output vector and continue until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns empty string; decode of empty string returns empty vector.
 * * Strings that are empty (`""`) are encoded as `"0/"` and correctly decoded.
 * * All possible characters (including digits and the delimiter) are safely handled because the delimiter is only examined **outside** the length field.
 *
 * --- Complexity ---
 * Time Complexity:  O(total length of all strings) for both encode and decode.
 * Space Complexity: O(total length of all strings) for the encoded string and the decoded vector.
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
            // read length
            size_t j = i;
            while (j < n && s[j] != '/') ++j;
            // j now points to the delimiter
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr);   // safe for large lengths
            i = j + 1;                      // skip delimiter

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
