/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that never appears in the length itself. During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `s` in the input vector, append `to_string(s.size())`, a special separator `'/'`, and then `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * If the encoded string is empty, return an empty vector.
 * * Scan the string from left to right.
 * * Find the next separator `'/'`; the substring before it is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. The separator `'/'` is safe because it never appears inside the numeric length prefix, guaranteeing an unambiguous split.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / vector (aside from the input storage).
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
            encoded += '/';          // separator between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // locate separator
            size_t slashPos = s.find('/', i);
            // malformed input guard (should not happen in LeetCode tests)
            if (slashPos == string::npos) break;

            // length substring -> integer
            size_t len = stoull(s.substr(i, slashPos - i));

            // extract the actual string
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // move cursor forward
            i = start + len;
        }
        return result;
    }
};
