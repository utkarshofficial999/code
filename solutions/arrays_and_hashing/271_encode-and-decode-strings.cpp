/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works even if the original string contains any possible character.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `s` in the input vector:
 * – Append `to_string(s.size())` → the length.
 * – Append a delimiter character `'/'`.
 * – Append the string `s` itself.
 * * Concatenate all parts into one big string and return it.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'/'` is found – this substring is the length `len`.
 * * Convert `len` to an integer.
 * * The next `len` characters form the original string; push it into the result vector.
 * * Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. The delimiter `'/'` is safe because the length field is numeric, so `'/'` can never appear inside it.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (each character is processed a constant number of times).
 * Space Complexity: O(N) for the output of encode and for the vector returned by decode (the algorithm itself uses only O(1) auxiliary space).
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
            encoded += '/';          // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move past '/'

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;                       // move to the start of next length field
        }
        return result;
    }
};
