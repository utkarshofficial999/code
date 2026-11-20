/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator that never appears in the length itself. During decoding we read the length, skip the separator, and extract exactly that many characters. This makes the process linear and immune to any characters inside the original strings (including the separator).
 *
 * --- Approach ---
 * 1. **Encoding**
 * - For every string `s` in the input vector, append `to_string(s.size())`, then a delimiter (e.g., `'#'`), then the string itself to the result.
 * - The delimiter is chosen because it never occurs in the numeric length representation.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Read characters until the delimiter `'#'` to obtain the length `len`.
 * - Convert `len` to an integer, then take the next `len` characters as the original string.
 * - Continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * - Strings that are empty (`""`) are encoded as `"0#"` and correctly decoded back to `""`.
 * - All possible ASCII characters (including `'#'`) are safely handled because the delimiter is only examined **outside** the actual string content (it follows the length field).
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the vector produced by decoding.
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
            encoded += '#';               // delimiter between length and content
            encoded += s;                 // actual string (may contain any character)
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
            i = j + 1; // move past '#'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of next length field
        }
        return result;
    }
};
