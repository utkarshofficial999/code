/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a non‑numeric separator.
 * During decoding we first read the length (digits until the separator), then extract exactly that many characters – this works even if the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `s` in the input vector, append `to_string(s.size())`, a special separator (e.g., `'#'`), and the string itself to the result.
 * * The separator is chosen to be a character that never appears in the length representation (digits only), so it can be safely used to locate the end of the length field.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the separator `'#'` – this substring is the length `len`.
 * * Convert `len` to an integer (`stoll` to avoid overflow).
 * * The next `len` characters form the original string; push it into the answer vector.
 * * Move the cursor past those `len` characters and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty.
 * * Empty encoded string → decoded vector is empty.
 * * Strings may be empty, contain digits, the separator, or any other ASCII/Unicode characters – the length‑prefix guarantees correct reconstruction.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the output of both functions (the encoded string or the vector of decoded strings).
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
            encoded += '#';          // separator (non‑digit)
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find separator '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // length substring is s[i..j-1]
            long long len = stoll(s.substr(i, j - i));
            i = j + 1; // move past '#'

            // extract the original string of length len
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
