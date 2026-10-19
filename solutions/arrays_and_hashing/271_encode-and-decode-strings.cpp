/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator (e.g., ‘/’) and then the string itself.
 * During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, compute `len = str.size()`.
 * * Append `len`, a delimiter `'/'`, and the string itself to a result `std::string`.
 * * The delimiter is chosen because it never appears inside the decimal representation of `len`.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length `len` of the next original string.
 * * Convert the substring before the delimiter to an integer.
 * * Move the cursor past the delimiter and take the next `len` characters as the original string.
 * * Repeat until the whole encoded string is consumed.
 * 
 * 3. Return the reconstructed vector of strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character a constant number of times).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures besides a few indices).
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
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // It is guaranteed to exist in a valid encoding
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move past '/'

            result.emplace_back(s.substr(i, len));
            i += len;                       // skip the extracted string
        }
        return result;
    }
};
