/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that cannot appear in the length itself (the delimiter is a non‑digit character). During decoding we read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `str` in the input vector:
 * – Append `to_string(str.size())`.
 * – Append a single delimiter character (e.g., '`/`').
 * – Append the string `str` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token:
 * – Read consecutive digits to obtain the length `len`.
 * – The next character must be the delimiter; skip it.
 * – Take the next `len` characters as the original string and push it into the answer vector.
 * – Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. The algorithm works for empty strings (`len = 0`) and for any characters inside the original strings because the delimiter is never part of the length field.
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
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';               // delimiter (non‑digit)
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
            size_t len = 0;
            while (i < n && isdigit(s[i])) {
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            // skip delimiter
            if (i >= n || s[i] != '/') {
                // malformed input – in LeetCode this never happens,
                // but we guard against it.
                break;
            }
            ++i; // move past '/'

            // extract the original string of length 'len'
            string cur = s.substr(i, len);
            result.push_back(std::move(cur));
            i += len;
        }
        return result;
    }
};
