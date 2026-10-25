/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘#’).
 * During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'#'`, then `s` itself to the result string.
 * * The delimiter is guaranteed to appear **after** the length, so the length can be parsed unambiguously.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until `'#'` is encountered – this substring is the decimal representation of the next string’s length.
 * * Convert it to an integer `len`.
 * * The next `len` characters form the original string; append it to the answer vector.
 * * Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. Both functions run in linear time with respect to the total number of characters in all strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the sum of lengths of all strings (including delimiters).
 * Space Complexity: O(N) for the encoded string and the output vector.
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
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr);   // length of the next string
            i = j + 1;                     // move past '#'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;                      // move to the start of the next length field
        }
        return result;
    }
};
