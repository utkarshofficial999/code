/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length followed by a delimiter that can never appear inside the length representation (e.g., ‘/’). During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the encoding unambiguous even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `std::string ans`.
 * * For every string `w` in the input vector:
 * – Append `std::to_string(w.size())`.
 * – Append a single delimiter character (we use ‘/’).
 * – Append the string `w` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token:
 * – Read characters until the delimiter ‘/’ is met; those characters form the decimal length `len`.
 * – Convert `len` to an integer.
 * – The next `len` characters belong to the original string; copy them into the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * * Return the vector of recovered strings.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Strings may be empty, contain delimiters, spaces, or any ASCII/Unicode characters – the length‑prefix guarantees correct reconstruction.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encode and decode scan each character once).
 * Space Complexity: O(N) for the output (the encoded string or the decoded vector).
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
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter that never appears in the length part
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
            i = j + 1;                     // skip delimiter

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;                      // move to the start of next token
        }
        return result;
    }
};
