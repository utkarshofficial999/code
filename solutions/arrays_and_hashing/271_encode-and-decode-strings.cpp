/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). The separator never appears inside the length field, so during decoding we can read the length, skip the separator, and extract exactly that many characters. This makes the encoding unambiguous even when the original strings contain any possible characters, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `s` in the input vector:
 * – Compute `len = s.size()`.
 * – Append `to_string(len)`, then a single delimiter `'/'`, then the string `s` itself to the result.
 * * Return the concatenated result.
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token:
 * – Read characters until the delimiter `'/'` is found → this substring is the length `len`.
 * – Convert `len` to an integer.
 * – The next `len` characters form the original string; append it to the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 3. The algorithm works for empty strings, empty vector, and strings that contain any characters (including `'/'`) because the delimiter only separates the length field, not the payload.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (each character is visited a constant number of times during encoding and decoding).
 * Space Complexity: O(N) for the output string (encoding) or the output vector (decoding); auxiliary space is O(1) besides the result containers.
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
            encoded += '/';          // delimiter separating length and content
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // It must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, stop

            // length substring [i, slashPos)
            size_t len = 0;
            // manual conversion to avoid extra string allocation
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // extract the actual string of length 'len'
            size_t start = slashPos + 1;
            string token = s.substr(start, len);
            result.push_back(std::move(token));

            // move index past the extracted token
            i = start + len;
        }
        return result;
    }
};
