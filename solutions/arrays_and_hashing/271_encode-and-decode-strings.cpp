/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. While decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings (including the delimiter itself).
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `s` in the input vector:
 * – Append `to_string(s.size())` (the length).
 * – Append a special delimiter, e.g. `'/'`.
 * – Append the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Read characters until the delimiter `'/'` to obtain the length `len`.
 * – Convert the collected characters to an integer.
 * – The next `len` characters form the original string; extract them and push into the answer vector.
 * – Move the cursor past the extracted part and repeat until the end of the encoded string.
 * 
 * 3. Handle corner cases automatically:
 * * Empty input vector → encoded string is empty.
 * * Empty strings inside the vector → length `0` is stored, and decoding correctly yields an empty string.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length delimiters).
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
                         + strs.size()*5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter between length and string
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& data) {
        vector<string> result;
        size_t i = 0, n = data.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && data[j] != '/') ++j;
            // j now points to delimiter
            string lenStr = data.substr(i, j - i);
            size_t len = stoull(lenStr);   // safe for large lengths
            i = j + 1;                     // skip delimiter

            // extract the string of length 'len'
            result.emplace_back(data.substr(i, len));
            i += len;                      // move to next encoded block
        }
        return result;
    }
};
