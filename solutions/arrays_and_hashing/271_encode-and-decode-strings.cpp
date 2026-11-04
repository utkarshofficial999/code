/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator. Knowing the exact length lets us extract the original string without ambiguity, even if the string itself contains the separator character.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, compute its length `len`.
 * * Append `len`, a delimiter (e.g., `'#'`), and then `str` itself to the result string.
 * * The final concatenated string represents the whole list.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'#'` to obtain the length substring, convert it to an integer `len`.
 * * The next `len` characters after the delimiter form the original string – push it into the answer vector.
 * * Advance the cursor past the processed part and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are handled naturally because their length is `0`.
 * * Use `size_t` (or `uint64_t`) for lengths to avoid overflow on very long strings.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length delimiters).
 * Space Complexity: O(N) for the encoded string and the decoded vector (output).
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
            encoded += '#';          // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter that separates length and string
            size_t delimPos = s.find('#', i);
            // safety check – malformed input would break here
            if (delimPos == string::npos) break;

            // extract length
            size_t len = stoull(s.substr(i, delimPos - i));

            // extract the actual string
            size_t start = delimPos + 1;
            result.emplace_back(s.substr(start, len));

            // move cursor forward
            i = start + len;
        }
        return result;
    }
};
