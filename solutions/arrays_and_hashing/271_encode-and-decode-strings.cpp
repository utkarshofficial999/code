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
 * During decoding we can read the length, skip the separator, and then extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `std::string ans`.
 * * For every string `w` in the input vector:
 * – Append `std::to_string(w.size())`, then a single delimiter `'/'`, then the string `w` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` with an index `i = 0`.
 * * While `i < s.size()`:
 * – Read characters until `'/'` to obtain the length `len` (as an integer).
 * – Move `i` past the delimiter.
 * – Extract the next `len` characters as one original string and push it into the answer vector.
 * – Advance `i` by `len`.
 * * Return the reconstructed vector.
 * 
 * Both steps run in linear time with respect to the total number of characters processed.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the sum of lengths of all strings (including delimiters).
 * Space Complexity: O(N) for the output of encode and for the vector returned by decode.
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

        for (const string& w : strs) {
            encoded += to_string(w.size());
            encoded += '/';
            encoded += w;
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
            // j now points to the delimiter
            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // skip delimiter

            decoded.emplace_back(s.substr(i, len));
            i += len;
        }
        return decoded;
    }
};
