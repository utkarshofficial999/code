/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length representation. While decoding we can read the length, skip the separator and extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, a special delimiter (e.g. '`/`'), and then `s` itself to the result string.
 * * The delimiter is safe because it never occurs inside the numeric length.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`/`' – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. Return the reconstructed vector.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector.
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
        encoded.reserve(strs.size() * 10); // small reservation, grows as needed
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter separating length and content
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
            // safety check – malformed input would break, but LeetCode guarantees correctness
            if (slashPos == string::npos) break;
            // length of the next string
            size_t len = stoull(s.substr(i, slashPos - i));
            // start of the actual string
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));
            i = start + len;
        }
        return result;
    }
};
