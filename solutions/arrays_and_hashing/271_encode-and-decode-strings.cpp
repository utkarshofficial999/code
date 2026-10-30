/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the process independent of the characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Initialise an empty result string.
 * * For every string `str` in the input vector:
 * – Append `to_string(str.size())` (the length).
 * – Append a special delimiter, e.g. `'/'`.
 * – Append the string `str` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Locate the next delimiter `'/'` to obtain the length substring.
 * – Convert this substring to an integer `len`.
 * – The actual string starts right after the delimiter and spans `len` characters.
 * – Extract that substring, push it into the answer vector, and move the cursor past it.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (e.g., `"0/"`).
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length delimiters).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
    string encode(vector<string>& strs) {
        string encoded;
        encoded.reserve(strs.size() * 10); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter separating length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> decoded;
        size_t i = 0;
        while (i < s.size()) {
            // find delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // safety check (should never happen for valid input)
            if (slashPos == string::npos) break;
            // extract length
            size_t len = stoull(s.substr(i, slashPos - i));
            // extract the actual string
            size_t start = slashPos + 1;
            decoded.emplace_back(s.substr(start, len));
            // move cursor forward
            i = start + len;
        }
        return decoded;
    }
};
