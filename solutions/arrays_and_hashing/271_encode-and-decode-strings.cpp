/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’). The separator never appears inside the length representation, so during decoding we can reliably read the length, skip the separator, and extract exactly that many characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then the string itself to the result.
 * - Concatenating all such blocks yields a single encoded string.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter `'/'`; the substring before it is the length `len`.
 * - Convert `len` to an integer (`size_t`).
 * - The next `len` characters form the original string; add it to the answer vector.
 * - Move the cursor past the extracted block and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → returns an empty string.
 * - Empty encoded string → returns an empty vector.
 * - Strings may contain any characters (including digits and `'/'`) because the delimiter separates the length from the payload, not the payload from itself.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the output).
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

    // Decode a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0;
        while (i < s.size()) {
            // Find the delimiter that ends the length field.
            size_t slashPos = s.find('/', i);
            // Extract length.
            size_t len = stoull(s.substr(i, slashPos - i));
            // Move cursor to the start of the actual string.
            i = slashPos + 1;
            // Extract the original string of length 'len'.
            result.emplace_back(s.substr(i, len));
            // Advance cursor past this string.
            i += len;
        }
        return result;
    }
};
