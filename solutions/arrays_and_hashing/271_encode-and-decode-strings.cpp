/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears in the length representation. During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `std::string ans`.
 * * For every string `s` in the input vector:
 * - Append `std::to_string(s.size())`, then a single delimiter `'/'`, then the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length substring, convert it to an integer (`size_t`).
 * * The characters immediately after the delimiter, of that length, form the original string – push it into the answer vector.
 * * Move the scanning index past the extracted string and repeat until the end of the encoded string.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter `'/'` never appears inside the length field (it contains only digits), so the split point is unambiguous.
 * * Length‑prefixed encoding handles empty strings (`"0/"`) and strings containing any characters, including `'/'`.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encode and decode scan each character a constant number of times).
 * Space Complexity: O(N) for the output string / vector (aside from the input itself).
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), (size_t)0,
                                            [](size_t sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

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
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // safety check (should never happen for valid input)
            if (slashPos == string::npos) break;

            // length substring [i, slashPos)
            size_t len = stoull(s.substr(i, slashPos - i));

            // start of actual string
            size_t start = slashPos + 1;
            // extract the string of length len
            result.emplace_back(s.substr(start, len));

            // move i to the next encoded block
            i = start + len;
        }
        return result;
    }
};
