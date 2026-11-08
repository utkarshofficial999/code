/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length representation. During decoding we can read the length, skip the separator, and extract exactly that many characters – guaranteeing a loss‑less round‑trip even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector, append `to_string(str.size())`, a single separator character (e.g., '`/`'), and then the string itself to the result.
 * * Concatenating all such blocks yields a single encoded string.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Locate the next separator '`/`' to obtain the length of the upcoming original string.
 * * Convert the substring before the separator to an integer `len`.
 * * The original string occupies the next `len` characters; copy them into the answer vector.
 * * Move the cursor past the extracted block and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (e.g., "`0/`").
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the decoded vector (output).
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
            encoded += '/';          // separator that never appears in the length part
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
            // sanity check (should never happen for valid input)
            if (slashPos == string::npos) break;

            // length of the next original string
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1; // move past '/'

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next block
        }
        return result;
    }
};
