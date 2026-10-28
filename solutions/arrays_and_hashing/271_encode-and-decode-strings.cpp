/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation (e.g., ‘#’). During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the process deterministic even when the original strings contain any possible characters, including the delimiter itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a special delimiter `'#'`, then the string `s` itself to the result.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token, read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (`"0#"`).
 * * Very long strings are supported because we store the length as a decimal number; `size_t` safely holds lengths up to the limits of the platform.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length delimiters).
 * Space Complexity: O(N) for the encoded string and the decoded vector.
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

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve(strs.size() * 10); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter separating length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& data) {
        vector<string> result;
        size_t i = 0;
        const size_t n = data.size();

        while (i < n) {
            // find delimiter '#'
            size_t delimPos = data.find('#', i);
            // delimiter must exist in a valid encoding
            if (delimPos == string::npos) break; // malformed input, stop

            // extract length
            size_t len = 0;
            // manual conversion to avoid overflow issues with stoi on huge numbers
            for (size_t j = i; j < delimPos; ++j) {
                len = len * 10 + (data[j] - '0');
            }

            // move i to the start of the actual string content
            i = delimPos + 1;
            // extract the string of length 'len'
            result.emplace_back(data.substr(i, len));
            i += len; // advance to the next encoded block
        }
        return result;
    }
};

/*
The LeetCode platform expects the class name to be `Codec` with the two
public methods `encode` and `decode`. The above implementation follows that
contract and works for all edge cases described.
*/
