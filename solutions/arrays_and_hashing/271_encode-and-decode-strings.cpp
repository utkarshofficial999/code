/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator that never appears in the length itself (digits). While decoding we can read the length, skip the separator and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, a delimiter (e.g., `'#'`), and then `s` itself to the result string.
 * * The delimiter is safe because the length is represented only by decimal digits, never `'#'`.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Find the next delimiter `'#'` – the substring before it is the length `len`.
 * * Convert `len` to an integer (`size_t`).
 * * The next `len` characters after the delimiter form the original string; push it into the answer vector.
 * * Move the scanning index past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns empty string; decode of empty string returns empty vector.
 * * Empty strings inside the list are handled because their length is `0` (`"0#"`).
 * * Use `size_t`/`stoull` to avoid overflow for very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_characters) – each character is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_characters) – the encoded string and the output vector together store all characters plus a small constant overhead.
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
        encoded.reserve(strs.size() * 10); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();
        while (i < n) {
            // locate delimiter
            size_t delim = s.find('#', i);
            // safety check (should never happen for valid input)
            if (delim == string::npos) break;
            // length of the next string
            size_t len = stoull(s.substr(i, delim - i));
            // extract the string
            size_t start = delim + 1;
            decoded.emplace_back(s.substr(start, len));
            // move to the next encoded part
            i = start + len;
        }
        return decoded;
    }
};
