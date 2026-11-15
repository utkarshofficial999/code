/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter `'/'`, and the string itself to the result.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length of the upcoming original string.
 * * Convert the length substring to an integer, then read exactly that many characters after the delimiter – this is one original string.
 * * Append the extracted string to the answer vector and continue until the whole encoded string is processed.
 * 
 * 3. Handle corner cases:
 * * Empty input vector → encoded string is empty.
 * * Empty encoded string → decoded vector is empty.
 * * The delimiter `'/'` is safe because the length field is numeric, never containing `'/'`.
 *
 * --- Complexity ---
 * Time Complexity:  O(total number of characters) for both encode and decode.
 * Space Complexity: O(total number of characters) for the output (the encoded string or the decoded vector).
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
        encoded.reserve(strs.size() * 10); // small reservation to reduce reallocations
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter that separates length and string
            size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            int len = stoi(s.substr(i, slashPos - i));
            i = slashPos + 1;                     // move past '/'
            result.emplace_back(s.substr(i, len));
            i += len;                             // skip the extracted string
        }
        return result;
    }
};
