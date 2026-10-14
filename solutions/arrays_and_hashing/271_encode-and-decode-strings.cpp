/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length followed by a unique separator (e.g., ‘:’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector.
 * * For each string `s`, append `to_string(s.size())`, then a separator `':'`, then `s` itself to the result string.
 * * The concatenated result is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next separator `':'` to obtain the length field.
 * * Convert the length substring to an integer `len`.
 * * The next `len` characters form the original string – push it into the answer vector.
 * * Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character is processed a constant number of times during encoding and decoding.
 * Space Complexity: O(total_chars) – the encoded string and the decoded vector together store all characters once.
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
            encoded += ':';          // separator that never appears in the length field
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find separator to extract length
            size_t sep = s.find(':', i);
            // safety check – malformed input (should not happen on LeetCode)
            if (sep == string::npos) break;
            int len = stoi(s.substr(i, sep - i));
            i = sep + 1;                     // move past ':'
            result.emplace_back(s.substr(i, len));
            i += len;                        // skip the extracted string
        }
        return result;
    }
};
