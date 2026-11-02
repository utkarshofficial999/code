/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a fixed separator. Knowing the exact length lets us read the original string even if it contains the separator character, guaranteeing a loss‑less round‑trip.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a separator (e.g., `':'`), and then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the separator `':'` to obtain the length `len`.
 * * Convert `len` to an integer, then extract the next `len` characters as the original string.
 * * Continue until the end of the encoded string and collect all extracted strings in a vector.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
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
    // Encode a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += ':';               // separator that never appears in the length field
            encoded += s;                 // the actual string (may be empty)
        }
        return encoded;
    }

    // Decode a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find separator to get the length
            size_t sep = s.find(':', i);
            // malformed input guard (should not happen in LeetCode tests)
            if (sep == string::npos) break;

            // length substring [i, sep)
            size_t len = 0;
            for (size_t j = i; j < sep; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the string of length 'len' after the separator
            size_t start = sep + 1;
            string cur = s.substr(start, len);
            result.push_back(std::move(cur));

            // move index to the beginning of the next encoded block
            i = start + len;
        }
        return result;
    }
};
