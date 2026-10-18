/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the process deterministic even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Initialise an empty result string.
 * - For every string `s` in the input vector, append `to_string(s.size())`, a chosen delimiter (e.g., '`/`'), and then `s` itself.
 * - Return the concatenated result.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter '`/`' to obtain the length field. Convert this substring to an integer (`size_t`).
 * - Starting after the delimiter, take `len` characters as the original string and push it into the answer vector.
 * - Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge‑case handling**
 * - Empty input vector → encoded string is empty, decoding returns an empty vector.
 * - Empty strings inside the vector are correctly encoded as `"0/"` and decoded back to `""`.
 * - Use `size_t`/`stoull` to avoid overflow for very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times).
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
        encoded.reserve( // optional reservation to avoid many reallocations
            accumulate(strs.begin(), strs.end(), 0ULL,
                       [](size_t sum, const string& s) { return sum + s.size() + 20; }));
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter that separates length from data
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
            size_t delimPos = s.find('/', i);
            // length substring is [i, delimPos)
            size_t len = stoull(s.substr(i, delimPos - i));
            // actual string starts after delimiter
            size_t start = delimPos + 1;
            result.emplace_back(s.substr(start, len));
            i = start + len; // move to next encoded block
        }
        return result;
    }
};
