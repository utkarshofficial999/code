/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length followed by a special separator.
 * During decoding we can read the length, skip the separator and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector:
 * – Append `to_string(str.size())` (its length).
 * – Append a delimiter character that never appears in the length representation, e.g. `'/'`.
 * – Append the string itself.
 * * Concatenate all parts into a single result string.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Locate the next delimiter `'/'` to obtain the length substring.
 * – Convert this substring to an integer `len`.
 * – The next `len` characters after the delimiter form the original string; add it to the answer.
 * – Move the cursor past the extracted string and repeat until the end.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter separates the length from the string, and the length tells us exactly how many characters belong to the string, so any character (including the delimiter) inside the original string is safely handled.
 * * An empty string is encoded as `"0/"` and decoded back correctly.
 * * An empty vector yields an empty encoded string and decodes to an empty vector.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the vector produced by decoding.
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
            // find delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // length field must exist; if not, malformed input (LeetCode guarantees well‑formed)
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move past delimiter
            result.emplace_back(s.substr(i, len));
            i += len;                       // skip the extracted string
        }
        return result;
    }
};
