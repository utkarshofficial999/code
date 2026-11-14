/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘#’). Because the length tells us exactly how many characters belong to the next string, the original strings can contain any character, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `w`, append `to_string(w.size())`, then a delimiter `'#'`, then the string itself to the result.
 * * The concatenated result is the encoded single string.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then extract the next `len` characters as the original string.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined.
 * Space Complexity: O(N) for the output of encode and the vector returned by decode (the algorithm itself uses only O(1) extra space).
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
        // Reserve approximate size to avoid many reallocations
        size_t total = 0;
        for (const auto& s : strs) total += s.size() + 10; // extra for length and '#'
        encoded.reserve(total);

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // Find delimiter '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // Extract length
            size_t len = 0;
            // stoi on substring is safe because we know it contains only digits
            len = static_cast<size_t>(stoll(s.substr(i, j - i)));
            // Move past '#'
            i = j + 1;
            // Extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
