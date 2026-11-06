/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length itself. During decoding we can read the length, skip the separator, and extract exactly that many characters – guaranteeing a loss‑less round‑trip even for empty strings or strings containing any characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Initialise an empty result string.
 * * For every string `str` in the input vector, append `to_string(str.size())`, a special separator (e.g., '`/`'), and then `str` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Locate the next separator '`/`' to obtain the length of the upcoming original string.
 * * Convert the substring before the separator to an integer `len`.
 * * The original string occupies the next `len` characters; extract it and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input list → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the list are handled because their length is `0` and we still store the separator.
 *
 * --- Complexity ---
 * Time Complexity:  O(total number of characters) for both encode and decode.
 * Space Complexity: O(total number of characters) for the encoded string and the output vector.
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
                         + strs.size() * 5 ); // rough reservation

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
            // slashPos must exist because encode always adds it
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move past '/'

            result.emplace_back(s.substr(i, len));
            i += len;                       // skip the extracted string
        }
        return result;
    }
};
