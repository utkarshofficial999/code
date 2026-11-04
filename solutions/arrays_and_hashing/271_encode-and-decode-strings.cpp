/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears in the length representation. During decoding we can read the length, skip the separator and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Initialise an empty `std::string ans`.
 * * For every string `s` in the input vector:
 * – Append `std::to_string(s.size())` (the length).
 * – Append a delimiter, e.g. `'/'`.
 * – Append the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Find the position of the next delimiter `'/'`.
 * – Convert the substring before the delimiter to an integer `len`.
 * – The actual string starts right after the delimiter and spans `len` characters.
 * – Extract that substring, push it into the answer vector, and move the cursor past it.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter `'/'` never appears inside the length field (which consists only of digits), so the split is unambiguous.
 * * Because we read exactly `len` characters for each token, any character (including `'/'`) inside the original strings is safely preserved.
 * * Handles empty strings (`len == 0`) and an empty input vector (produces an empty encoded string).
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / vector (the algorithm uses only a few auxiliary variables besides the required output).
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
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter that separates length and the actual string
            size_t slashPos = s.find('/', i);
            // slashPos must exist because encoding always adds it
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move to start of the actual string
            decoded.emplace_back(s.substr(i, len));
            i += len;                       // skip the extracted string
        }
        return decoded;
    }
};
