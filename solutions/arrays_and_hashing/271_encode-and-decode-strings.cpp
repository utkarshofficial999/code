/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears in the length representation. During decoding we can read the length, skip the separator and extract exactly that many characters – this works for any possible characters inside the original strings (including the separator itself).
 *
 * --- Approach ---
 * 1. **Encode** (`string encode(vector<string>& strs)`)
 * * For every string `s` in `strs`
 * * Append `to_string(s.size())` → the length.
 * * Append a delimiter (choose `'#'`).
 * * Append the string `s` itself.
 * * Concatenate all parts into one big string and return it.
 * 
 * 2. **Decode** (`vector<string> decode(string s)`)
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'#'` – this substring is the length `len`.
 * * Convert `len` to an integer.
 * * The next `len` characters belong to the original string; extract them and push into the result vector.
 * * Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * Both steps run in linear time with respect to the total number of characters in all strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all input strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector (the algorithm uses only a few extra variables).
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
    string encode(vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';               // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // safety: malformed input (should not happen in LeetCode tests)
            if (j == n) break;

            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // skip delimiter

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
