/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each original string by prefixing it with its length and a special separator.
 * During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector, compute its length `len`.
 * * Append `len` (as decimal) followed by a delimiter (e.g., '`/`') and then the string itself to the result.
 * * Concatenating all such blocks yields a single encoded string.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`/`' – this gives the length of the next original string.
 * * Convert the length to an integer, then take the next `len` characters as the original string and store it.
 * * Move the cursor past the extracted block and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty, decoding returns an empty vector.
 * * Empty strings inside the vector are handled because their length is `0` (encoded as "`0/`").
 * * The delimiter '`/`' is safe because we never rely on its absence inside the original string – the length tells us exactly where the string ends.
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
                         + strs.size()*5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';               // delimiter separating length and content
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
            size_t len = stoull(s.substr(i, j - i));
            i = j + 1; // skip delimiter

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
