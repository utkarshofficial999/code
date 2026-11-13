/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator.
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `result` string.
 * * For every string `s` in the input vector:
 * - Append `to_string(s.size())`, then a delimiter (choose `'/'`), then `s` itself.
 * * Return the concatenated `result`.
 * * The delimiter is safe because the length tells us exactly where the next string starts, regardless of the delimiter’s presence inside `s`.
 * 
 * 2. **Decode**
 * * Initialise an empty vector `out`.
 * * Scan the encoded string with an index `i`.
 * * While `i` is less than the string size:
 * - Read characters until the delimiter `'/'` to obtain the length `len`.
 * - Convert the collected digits to an integer (`size_t`).
 * - Move `i` past the delimiter, then take the next `len` characters as the original string and push it into `out`.
 * - Advance `i` by `len`.
 * * Return `out`.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → empty encoded string.
 * * Empty encoded string → empty output vector.
 * * Strings may be empty; they are encoded as `"0/"` and decoded correctly.
 * * Use `size_t` for lengths to avoid overflow on very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character of the input appears once in encoding and once in decoding.
 * Space Complexity: O(total_chars) – the encoded string and the output vector together store the same amount of data as the original strings.
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
            encoded += '/';          // delimiter
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
            size_t len = 0;
            while (i < n && s[i] != '/') {
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            ++i; // skip the delimiter '/'
            // extract the string of length 'len'
            decoded.emplace_back(s.substr(i, len));
            i += len;
        }
        return decoded;
    }
};
