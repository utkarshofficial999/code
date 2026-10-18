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
 * 1. **Encoding**
 * * Initialise an empty `result` string.
 * * For every string `s` in the input vector:
 * – Append `to_string(s.size())` (the length).
 * – Append a delimiter character (we use '`/`', which never appears in the numeric length).
 * – Append the string `s` itself.
 * * Return the concatenated `result`.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each token:
 * – Find the next delimiter '`/`' to obtain the length substring.
 * – Convert that substring to an integer `len`.
 * – The next `len` characters after the delimiter form the original string; push it into the answer vector.
 * – Move the scanning index past the extracted string and repeat until the end of the encoded text.
 * 
 * 3. **Edge‑case handling**
 * * Empty input vector → encoded string is empty, decoding an empty string yields an empty vector.
 * * Empty strings inside the vector are encoded as `"0/"` and correctly decoded.
 * * Use `size_t`/`uint64_t` for lengths to avoid overflow on very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the output string / vector (the algorithm uses only a few extra variables besides the required output).
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0ULL,
                                            [](uint64_t sum, const string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // locate delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // sanity check – malformed input would break here, but LeetCode guarantees valid encoding
            if (slashPos == string::npos) break;

            // extract length
            uint64_t len = 0;
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = slashPos + 1;
            decoded.emplace_back(s.substr(start, (size_t)len));

            // move index to the start of the next encoded token
            i = start + (size_t)len;
        }
        return decoded;
    }
};
