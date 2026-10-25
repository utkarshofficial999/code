/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. During decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `w`, append `to_string(w.size())`, then a special delimiter (e.g., `'#'`), then the string itself to the result.
 * * The delimiter is safe because the length is a decimal number and never contains `'#'`.
 * 
 * 2. **Decoding**
 * * Scan the encoded string `s` from left to right.
 * * Read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the end of `s`.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty.
 * * Empty strings inside the vector → encoded as `"0#"` (length 0, no characters).
 * * Very long strings → use `size_t` (64‑bit on modern platforms) for length to avoid overflow.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times).
 * Space Complexity: O(N) for the encoded string (output) and O(N) for the decoded vector (input), besides O(1) auxiliary space.
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), (size_t)0,
                                            [](size_t sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

        for (const string& w : strs) {
            encoded += to_string(w.size());
            encoded += '#';               // delimiter between length and content
            encoded += w;                 // actual string (may be empty)
        }
        return encoded;
    }

    // Decode a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr); // safe for large lengths
            // move past delimiter
            i = j + 1;
            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // advance to next length field
        }
        return result;
    }
};
