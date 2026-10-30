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
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a single character `'/'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each token, read characters until `'/'` to obtain the length `len`.
 * * Convert the collected digits to an integer.
 * * Extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined.
 * Space Complexity: O(N) for the encoded string (and the output vector during decoding).
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
            encoded += '/';
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
            while (j < n && s[j] != '/') ++j;
            // j now points to the separator
            long long len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');
            }
            i = j + 1; // skip the '/'
            decoded.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return decoded;
    }
};
