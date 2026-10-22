/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself.
 * During decoding we read the length, skip the delimiter, and then extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Initialise an empty result string.
 * * For every string `s` in the input vector:
 * – Append `to_string(s.size())` (its length).
 * – Append a delimiter character, e.g. `'#'`.
 * – Append the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each token:
 * – Read characters until the delimiter `'#'` to obtain the length `len`.
 * – Convert the length substring to an integer (`stoull`).
 * – The next `len` characters form the original string; extract them and push into the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled naturally (`"0#"` is emitted).
 * * Use `size_t` / `unsigned long long` for lengths to avoid overflow for very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(total number of characters) for both encode and decode.
 * Space Complexity: O(total number of characters) for the encoded string and the decoded vector (output space).
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
        encoded.reserve( // optional reservation to reduce reallocations
            accumulate(strs.begin(), strs.end(), (size_t)0,
                       [](size_t sum, const string& s){ return sum + s.size() + 20; }));
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';               // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // length substring is s[i..j-1]
            unsigned long long len = 0;
            if (j > i) {
                len = stoull(s.substr(i, j - i));
            }
            i = j + 1; // skip delimiter
            // extract the original string of length len
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);
        }
        return result;
    }
};
