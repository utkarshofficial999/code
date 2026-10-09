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
 * During decoding we can read the length, skip the separator and extract exactly that many characters – no character in the original strings can break the parsing because the length tells us where each string ends.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `s` in the input vector, compute its length `len`.
 * * Append `len`, a delimiter (choose `':'` which never appears in the numeric length), and the string itself to the result.
 * * The final encoded string is the concatenation of all such blocks.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `':'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter separates the numeric length from the payload, so any character (including digits, delimiters, or null bytes) inside the original strings is safely stored because we never rely on its value – we always know exactly how many characters to read.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character a constant number of times).
 * Space Complexity: O(N) for the encoded string and the vector produced by decoding (output space).
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
            encoded += ':';               // delimiter between length and string
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
            while (j < n && s[j] != ':') ++j;
            // safety: malformed input (should not happen in LeetCode tests)
            if (j == n) break;

            long long len = 0;
            for (size_t k = i; k < j; ++k) {
                len = len * 10 + (s[k] - '0');
            }

            // extract the string of length 'len'
            size_t start = j + 1;
            size_t end = start + (size_t)len;
            // safety check
            if (end > n) break;

            result.emplace_back(s.substr(start, (size_t)len));
            i = end;
        }
        return result;
    }
};
