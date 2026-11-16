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
 * * Initialise an empty `std::string ans`.
 * * For every string `w` in the input vector:
 * – Append `std::to_string(w.size())`, then a separator `'/'`, then the string `w` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token:
 * – Locate the next separator `'/'` to obtain the length field.
 * – Convert the length substring to an integer `len`.
 * – The actual string starts right after the separator and spans `len` characters.
 * – Append this substring to the answer vector and move the cursor past it.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. The separator is chosen to be a character that never appears in the numeric length field, so the parsing is unambiguous even when the original strings contain `'/'`.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output (the encoded string or the decoded vector). No extra auxiliary space beyond the output.
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

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // separator between length and string
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find the separator that ends the length field
            size_t slashPos = s.find('/', i);
            // safety check – malformed input (should not happen in LeetCode)
            if (slashPos == string::npos) break;

            // length of the next original string
            size_t len = stoull(s.substr(i, slashPos - i));

            // start of the actual string
            size_t start = slashPos + 1;
            decoded.emplace_back(s.substr(start, len));

            // move cursor to the next encoded block
            i = start + len;
        }
        return decoded;
    }
};
