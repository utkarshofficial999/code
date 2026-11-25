/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator.
 * Because the length tells us exactly how many characters belong to the next string, the separator can appear inside the original strings without ambiguity.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (e.g., '`/`'), and then `s` itself to the result string.
 * * The final concatenated string represents the whole list.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`/`' – this substring is the length `len` of the next original string.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and store it in the answer vector.
 * * Move the cursor past the consumed part and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (e.g., "`0/`").
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encode and decode scan each character once).
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
            encoded += '/';          // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& data) {
        vector<string> result;
        size_t i = 0, n = data.size();

        while (i < n) {
            // find delimiter '/'
            size_t slashPos = data.find('/', i);
            // safety: if not found, malformed input – break
            if (slashPos == string::npos) break;

            // length substring [i, slashPos)
            size_t len = 0;
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (data[j] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = slashPos + 1;
            string cur = data.substr(start, len);
            result.push_back(std::move(cur));

            // move index past the extracted part
            i = start + len;
        }
        return result;
    }
};
