/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length representation. While decoding we can read the length, skip the separator, and then extract exactly that many characters – this makes the process deterministic for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `str` in the input vector:
 * – Append `to_string(str.size())` (the length).
 * – Append a special separator, e.g. `'/'`.
 * – Append the string `str` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Iterate over the encoded string with an index `i`.
 * * While `i` is less than the string size:
 * – Read characters until the separator `'/'` to obtain the length `len`.
 * – Convert the collected digits to an integer.
 * – Move `i` past the separator.
 * – Extract the next `len` characters as one original string and push it to the answer vector.
 * – Advance `i` by `len`.
 * * Return the reconstructed vector.
 * 
 * 3. The separator `'/'` is safe because it never appears in the numeric length prefix, guaranteeing an unambiguous split even if the original strings contain `'/'` or any other characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
        encoded.reserve(strs.size() * 10); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // separator between length and content
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
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr);   // safe for large lengths
            i = j + 1;                     // move past '/'

            // extract the string of length 'len'
            decoded.emplace_back(s.substr(i, len));
            i += len;                      // move to the start of next length field
        }
        return decoded;
    }
};
