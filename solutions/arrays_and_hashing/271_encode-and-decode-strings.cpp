/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length representation. During decoding we can read the length, skip the separator and extract exactly that many characters. This makes the process linear and works for any possible characters inside the original strings (including empty strings).
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, a special separator (e.g., `'#'`), and then `s` itself to the result string.
 * * The separator is safe because the length is a decimal number and never contains `'#'`.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the separator `'#'` is found – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. Return the reconstructed vector of strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
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
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // separator
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find separator '#'
            size_t sep = s.find('#', i);
            // safety check – malformed input should not happen in LeetCode tests
            if (sep == string::npos) break;

            // length of the next word
            size_t len = stoull(s.substr(i, sep - i));
            i = sep + 1; // move past '#'

            // extract the word
            result.emplace_back(s.substr(i, len));
            i += len;    // move to the start of the next length field
        }
        return result;
    }
};
