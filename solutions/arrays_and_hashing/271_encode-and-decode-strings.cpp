/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length itself.
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings (including the separator).
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `result` string.
 * * For every string `s` in the input vector:
 * - Append `to_string(s.size())`, then a special separator (e.g., '`/`'), then the string `s` itself.
 * * Return the concatenated `result`.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * - Locate the next separator '`/`' to obtain the length field.
 * - Convert the length substring to an integer `len`.
 * - The actual string starts right after the separator and spans `len` characters.
 * - Append this substring to the answer vector and move the cursor past it.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. The separator '`/`' is safe because it never appears inside the numeric length representation, guaranteeing an unambiguous split even when the original strings contain any characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
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
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';               // separator between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find the separator that ends the length field
            size_t slashPos = s.find('/', i);
            // (The problem guarantees a valid encoding, so slashPos will always be found)
            int len = stoi(s.substr(i, slashPos - i));
            i = slashPos + 1;                     // move past the separator
            decoded.emplace_back(s.substr(i, len));
            i += len;                             // move to the start of the next length field
        }
        return decoded;
    }
};
