/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself. While decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - For every string `str` in the input vector, append `to_string(str.size())`, a special delimiter (e.g., '`/`'), and then `str` itself to the result string.
 * - The delimiter separates the numeric length from the actual content; the length itself is unambiguous because it consists only of digits.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Read characters until the delimiter '`/`' is encountered – this substring is the length `len`.
 * - Convert `len` to an integer, then take the next `len` characters as the original string and store it in the output vector.
 * - Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * - Because the length is read before the delimiter, any character (including the delimiter) that appears inside the original string does not affect parsing.
 * - The algorithm works for empty strings, very long strings, and strings containing any ASCII/Unicode characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the result).
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
            encoded += '/';               // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '/') ++j;
            // j now points to the delimiter
            long long len = stoll(s.substr(i, j - i));
            i = j + 1; // skip delimiter

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
