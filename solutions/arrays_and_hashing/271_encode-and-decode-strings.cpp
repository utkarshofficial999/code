/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator. The decoder can read the length, skip the separator, and extract exactly that many characters, guaranteeing correct reconstruction even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (e.g., `'#'`), and then `s` itself to the result string.
 * * The delimiter is chosen because it never appears inside the numeric length representation.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert the collected digits to an integer.
 * * Extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (`"0#"`).
 * * All possible characters (including `'#'`) are safe because the delimiter is only examined **outside** the actual string content (after the length).
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times).
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
            encoded += '#';          // delimiter between length and content
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
            // j now points to delimiter; substring [i, j) are digits
            long long len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');
            }
            i = j + 1; // move past '#'

            // extract the string of length len
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
