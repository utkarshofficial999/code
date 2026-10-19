/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’).
 * During decoding we first read the length up to the separator, then extract exactly that many characters – this works for any possible characters inside the original strings, including digits and the separator itself.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, then a delimiter `'/'`, then the string itself to the result.
 * * The concatenated result is the encoded single string.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'`; the substring before it is the length `len`.
 * * Convert `len` to an integer (`size_t`).
 * * The next `len` characters form the original string – push it into the answer vector.
 * * Move the cursor past those `len` characters and repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge‑case handling**
 * * Empty input vector → returns an empty string.
 * * Empty strings inside the vector are encoded as `0/` and decoded correctly.
 * * All characters (including `'/'` and digits) are safely handled because the length is read before any content.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the output).
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
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(), 0ULL,
                                            [](unsigned long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation

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
            // find the delimiter that separates length and string
            size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;                     // move to start of actual string
            result.emplace_back(s.substr(i, len));
            i += len;                             // skip the extracted string
        }
        return result;
    }
};
