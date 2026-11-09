/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator that never appears in the length representation. During decoding we read the length, skip the separator, and extract exactly that many characters. This makes the process linear and immune to any characters that may be present inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (e.g., '`/`'), and then `s` itself to the result string.
 * * The delimiter is chosen because it never occurs in the decimal representation of a length, guaranteeing an unambiguous split.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter '`/`' to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted string and repeat until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The length prefix uniquely determines where each original string ends, regardless of its content.
 * * The algorithm works for empty strings, strings containing delimiters, and very large inputs because it never relies on any sentinel characters inside the payload.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length prefixes).
 * Space Complexity: O(N) for the encoded string and the vector produced by decode.
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
        encoded.reserve(strs.size() * 10); // rough reservation to reduce reallocations
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';               // delimiter that never appears in the length
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find the delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // safety check – the input is guaranteed to be produced by encode()
            if (slashPos == string::npos) break;

            // extract length
            size_t len = 0;
            // manual conversion avoids extra string allocation
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // move cursor to the start of the actual string
            i = slashPos + 1;
            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            // advance cursor past the extracted string
            i += len;
        }
        return result;
    }
};
