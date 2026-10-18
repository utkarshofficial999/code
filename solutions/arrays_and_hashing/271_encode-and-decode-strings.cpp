/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator.
 * During decoding we first read the length (up to the separator), then take exactly that many characters – the separator itself can appear inside the original string without ambiguity.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector, append `to_string(str.size())`, a delimiter `'/'`, and then `str` itself to the result string.
 * * The delimiter is chosen because it never appears in the numeric length prefix, so the boundary is uniquely identifiable.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length substring, convert it to an integer (`size_t`).
 * * Move past the delimiter and read exactly `len` characters – this is one original string.
 * * Repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → returns an empty string.
 * * Empty strings inside the vector → encoded as `"0/"` and correctly decoded.
 * * Very long strings → use `size_t`/`stoull` to avoid overflow.
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
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter that ends the length field
            size_t delim = s.find('/', i);
            // length substring is [i, delim)
            size_t len = stoull(s.substr(i, delim - i));
            i = delim + 1; // move past '/'

            // extract the original string of length len
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of next encoded block
        }
        return result;
    }
};
