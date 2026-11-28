/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each original string as `<length>/<string>` and concatenate them.
 * During decoding we can read the length up to the separator, then extract exactly that many characters – no character in the original data can break the parsing because the length tells us where the string ends.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, compute its length `len`.
 * * Append `len`, a special separator `'/'`, and the string itself to a result `std::string`.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next separator `'/'` to obtain the length of the next original string.
 * * Convert the substring before `'/'` to an integer `len`.
 * * Take the following `len` characters as the original string, push it into the answer vector, and move the cursor past them.
 * * Repeat until the whole encoded string is consumed.
 * 
 * 3. The separator `'/'` is safe because it never appears inside the length field (which consists only of digits). The actual data may contain `'/'`, but it is never interpreted as a delimiter because we always know the exact length of the data segment.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output of encode and for the vector returned by decode.
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
            encoded += '/';               // separator between length and data
            encoded += s;                 // the actual string (may contain '/')
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find the separator that ends the length field
            size_t slashPos = s.find('/', i);
            // The problem guarantees a valid encoding, so slashPos must be found
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;                     // move past '/'

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;                             // move to the start of next length field
        }
        return result;
    }
};
