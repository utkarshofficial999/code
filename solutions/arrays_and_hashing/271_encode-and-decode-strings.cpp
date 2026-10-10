/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that cannot appear in the length representation. During decoding we read the length, skip the delimiter, and extract exactly that many characters. This makes the process deterministic for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Initialise an empty result string.
 * - For every string `s` in the input vector, append `to_string(s.size())`, a single delimiter `'/'`, and then `s` itself.
 * - The delimiter separates the numeric length from the actual data; because the length is purely digits, `'/'` can never be confused with part of the length.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Locate the next `'/'` to obtain the substring that represents the length. Convert it to an integer (`size_t`).
 * - Move past the delimiter and take the next `len` characters as one original string.
 * - Continue until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encoded string is empty.
 * - Empty encoded string → decoded vector is empty.
 * - Strings may be empty, contain digits, slashes, or any other characters; the length prefix guarantees correct reconstruction.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0ULL,
                                            [](unsigned long long sum, const string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string back to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0;
        while (i < s.size()) {
            // find delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            if (slashPos == string::npos) break; // malformed input, safety guard

            // parse length
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1; // move past '/'

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // advance to the start of the next length field
        }
        return result;
    }
};
