/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘#’). During decoding we read the length, skip the separator, and extract exactly that many characters. The length prefix removes any ambiguity caused by characters that may also appear in the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'#'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each segment, read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the output vector.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter `'#'` never appears inside the length field (it consists only of digits).
 * * The exact length tells us where the next string starts, so any character (including `'#'`) inside the original strings is safely handled.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character of the input strings is visited once during encoding and once during decoding.
 * Space Complexity: O(total_chars) – the encoded string stores all characters plus a small constant‑size overhead per original string.
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
                         + strs.size() * 5 ); // rough reserve to avoid many reallocations
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter between length and string
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // substring [i, j) holds the length
            long long len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');   // safe because length fits in 64‑bit
            }
            // move past '#'
            i = j + 1;
            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);
        }
        return result;
    }
};
