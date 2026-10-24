/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator. The length tells us exactly how many characters belong to the next original string, so any character (including the separator itself) can appear safely inside the payload.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (chosen as '`/`'), and then `s` itself to the result string.
 * * The final concatenated string is returned.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`/`' to obtain the length `len` of the next original string.
 * * Convert the length substring to an integer.
 * * Extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → returns an empty string, and decoding an empty string yields an empty vector.
 * * Empty strings inside the vector are encoded as `"0/"` and correctly recovered.
 * * The delimiter never interferes because the length prefix disambiguates the payload.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter that separates length from data
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string back to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter to extract length
            size_t delim = s.find('/', i);
            // safety check (should never happen for valid input)
            if (delim == string::npos) break;

            int len = stoi(s.substr(i, delim - i));
            i = delim + 1;                     // move past delimiter
            result.emplace_back(s.substr(i, len));
            i += len;                          // skip the extracted string
        }
        return result;
    }
};
