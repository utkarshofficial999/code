/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation.
 * During decoding we can read the length, skip the delimiter, and extract exactly that many characters – guaranteeing a loss‑less round‑trip even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a special delimiter (e.g., `'#'`), then `s` itself to the result string.
 * * The delimiter is safe because it never occurs inside the decimal representation of the length.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each token, read characters until the delimiter `'#'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the end of `s`.
 * 
 * 3. The algorithm works for empty strings, strings containing `'#'`, and any Unicode/ASCII characters because the delimiter only separates the length field, not the payload.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_characters) – each character of the input is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_characters) – the encoded string stores all characters plus a small overhead for the length fields.
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
                         + strs.size() * 5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter
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
            size_t delim = s.find('#', i);
            // safety check (should never happen for a valid encoding)
            if (delim == string::npos) break;

            // length of the next string
            size_t len = stoull(s.substr(i, delim - i));
            i = delim + 1; // move past '#'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next length field
        }
        return result;
    }
};
