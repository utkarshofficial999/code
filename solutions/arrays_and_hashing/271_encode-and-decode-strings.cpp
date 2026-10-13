/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a delimiter that never appears in the length representation (e.g., ‘#’).
 * During decoding we read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings, including the delimiter itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a special delimiter `'#'`, then the string itself to the result.
 * * The concatenated result is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each segment, read characters until the delimiter `'#'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (`"0#"`).
 * * All characters (including `'#'`) are allowed inside the original strings because the delimiter is read **after** the length, not searched inside the payload.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length delimiters).
 * Space Complexity: O(N) for the encoded string and the decoded vector (output space).
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
            encoded += '#';          // delimiter separating length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter; substring [i, j) is the length
            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // skip delimiter

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
