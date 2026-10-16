/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a unique separator (e.g., ‘/’). Knowing the length lets us read the exact number of characters for the original string, so any character (including the separator) inside the string is safely handled.
 *
 * --- Approach ---
 * 1. **Encode**
 * - Iterate over the input vector.
 * - For each string `s`, append `to_string(s.size())`, then a separator `'/'`, then `s` itself to the result string.
 * - The concatenated result is the encoded single string.
 * 
 * 2. **Decode**
 * - Scan the encoded string from left to right.
 * - Locate the next separator `'/'` to obtain the length prefix.
 * - Convert the length substring to an integer `len`.
 * - Extract the next `len` characters as the original string and push it into the answer vector.
 * - Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character a constant number of times).
 * Space Complexity: O(N) for the output (the encoded string or the decoded vector). No extra auxiliary space beyond the output is used.
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
        encoded.reserve(strs.size() * 10); // small reservation, grows as needed
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // separator that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find the separator that ends the length field
            size_t sep = s.find('/', i);
            // length substring is [i, sep)
            int len = stoi(s.substr(i, sep - i));
            // the actual string starts after the separator
            size_t start = sep + 1;
            result.emplace_back(s.substr(start, len));
            i = start + len; // move to the next encoded block
        }
        return result;
    }
};
