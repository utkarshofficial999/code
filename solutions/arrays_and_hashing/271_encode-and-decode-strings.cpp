/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘#’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, then a delimiter `'#'`, then `s` itself to the result string.
 * * The concatenation of all such blocks is the encoded representation.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Find the next delimiter `'#'` – the substring before it is the length `len`.
 * * Convert `len` to an integer (`stoull`).
 * * The next `len` characters after the delimiter form the original string; push it into the answer vector.
 * * Move the scanning pointer past the extracted block and repeat until the whole string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter is never part of the length field, so parsing is unambiguous.
 * * Because we always read exactly `len` characters, any character (including ‘#’) inside the original strings is safely handled.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the output string in encode and for the resulting vector in decode.
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
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0;
        while (i < s.size()) {
            // locate delimiter that separates length and string
            size_t delim = s.find('#', i);
            // length substring -> integer
            size_t len = stoull(s.substr(i, delim - i));
            // extract the original string of length 'len'
            string str = s.substr(delim + 1, len);
            result.push_back(std::move(str));
            // advance pointer past the processed block
            i = delim + 1 + len;
        }
        return result;
    }
};
