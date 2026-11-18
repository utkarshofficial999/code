/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length followed by a delimiter that never appears in the length representation (e.g., ‘#’). During decoding we can read the length, skip the delimiter and extract exactly that many characters – no matter what characters the original strings contain.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, then a delimiter `'#'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each segment, read characters until the delimiter `'#'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string, decode of an empty string returns an empty vector.
 * * Strings may contain any characters (including ‘#’) because the delimiter separates the length from the content, not the content itself.
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
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

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
            // find delimiter '#'
            size_t delimPos = s.find('#', i);
            // safety: if not found, malformed input – break
            if (delimPos == string::npos) break;

            // length substring [i, delimPos)
            size_t len = 0;
            for (size_t j = i; j < delimPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = delimPos + 1;
            string cur = s.substr(start, len);
            result.push_back(std::move(cur));

            // move index to the start of the next encoded block
            i = start + len;
        }
        return result;
    }
};
