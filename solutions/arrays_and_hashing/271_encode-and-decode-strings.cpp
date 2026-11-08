/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a delimiter that never appears in the length itself. During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the process linear and immune to any characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, a special delimiter `'/'`, and then `s` itself to the result string.
 * - The delimiter separates the length field from the actual data; the length tells us exactly where the next encoded string starts, regardless of the characters inside `s`.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter `'/'` to obtain the length field. Convert it to an integer `len`.
 * - The original string starts right after the delimiter and spans `len` characters. Extract it and push it into the answer vector.
 * - Move the cursor past the extracted substring and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * - Strings may be empty, contain digits, slashes, or any other ASCII/Unicode characters – the length prefix guarantees correct parsing.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_characters) for both encode and decode (each character is visited a constant number of times).
 * Space Complexity: O(total_characters) for the encoded string and the output vector (no extra auxiliary structures beyond the result).
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
    // Encode a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( // reserve an estimate to avoid many reallocations
            accumulate(strs.begin(), strs.end(), 0LL,
                       [](long long sum, const string& s) { return sum + s.size() + 20; })
        );
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter separating length and data
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string back to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // length field must exist; if not, malformed input (not expected in LeetCode)
            int len = stoi(s.substr(i, slashPos - i));
            i = slashPos + 1;                 // move to start of actual string
            result.emplace_back(s.substr(i, len));
            i += len;                         // skip over the extracted string
        }
        return result;
    }
};
