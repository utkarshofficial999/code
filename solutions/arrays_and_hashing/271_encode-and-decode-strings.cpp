/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation (e.g., ‘#’). During decoding we can read the length, skip the delimiter, and extract exactly that many characters – guaranteeing a loss‑less round‑trip even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `std::string ans`.
 * * For every string `w` in the input vector:
 * – Append `std::to_string(w.size())`, then the delimiter `'#'`, then the string `w` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Read characters until the delimiter `'#'` to obtain the length `len`.
 * – Convert `len` to an integer.
 * – The next `len` characters form the original string; push it into the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Strings may contain any characters (including digits and ‘#’) because the delimiter separates the length from the payload, not the payload from each other.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the output of both functions (the encoded string or the vector of decoded strings).
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
            encoded += '#';          // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter; substring [i, j) is the length
            size_t len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');
            }
            i = j + 1; // skip delimiter

            // extract the original string of length 'len'
            decoded.emplace_back(s.substr(i, len));
            i += len;
        }
        return decoded;
    }
};
