/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length representation. During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `s` in the input vector, append `to_string(s.size())`, a special separator (e.g., '`/`'), and then `s` itself to the result string.
 * * The separator is chosen because it never occurs in the decimal representation of the length, guaranteeing an unambiguous split.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Locate the next separator '`/`' to obtain the length `len` of the upcoming original string.
 * * Convert the substring before the separator to an integer.
 * * Move the cursor past the separator and read exactly `len` characters – this is one original string.
 * * Repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Strings may be empty, contain any characters (including the separator) – the length prefix protects us from ambiguity.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the result).
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
            encoded += '/';          // separator that never appears in the length
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find separator '/'
            size_t slashPos = s.find('/', i);
            // slashPos must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, safety guard

            // length of the next original string
            size_t len = stoull(s.substr(i, slashPos - i));

            // start of the actual string
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // move cursor to the next encoded block
            i = start + len;
        }
        return result;
    }
};
