/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator.
 * Because the length is numeric, the separator can never be confused with the data, allowing us to decode by reading the length first and then extracting exactly that many characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `s` in the input vector, append `to_string(s.size())`, a delimiter (chosen as '`/`'), and the string itself to the result.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter '`/`' to obtain the length substring, convert it to an integer (`len`).
 * * The next `len` characters form the original string; store it in the answer vector.
 * * Move the cursor past the processed part and repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → empty encoded string.
 * * Empty string element (`""`) → encoded as `"0/"` and correctly decoded back to `""`.
 * * Very long strings → use `size_t`/`unsigned long long` for length to avoid overflow.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string (encoding) or the output vector (decoding); auxiliary space is O(1).
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
        encoded.reserve( // reserve a reasonable amount to avoid many reallocations
            accumulate(strs.begin(), strs.end(), 0ULL,
                       [](unsigned long long sum, const string& s) {
                           return sum + s.size() + 20; // extra for length and delimiter
                       }));
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter that never appears in the length part
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
            size_t slashPos = s.find('/', i);
            // It is guaranteed to exist in a valid encoding
            unsigned long long len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;                 // move past the delimiter
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);    // skip the extracted string
        }
        return result;
    }
};
