/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator that never appears in the length itself. While decoding we read the length, skip the separator, and extract exactly that many characters. Because the length tells us where a string ends, the original content (including any possible separator characters) is preserved.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (choose `'/'`), and then `s` itself to the result string.
 * * The delimiter is safe because it never occurs inside the numeric length representation.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted string and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Strings may contain any characters (including the delimiter) because the length tells us exactly how many characters belong to the string.
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
                         + strs.size() * 5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';          // delimiter separating length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& data) {
        vector<string> result;
        size_t i = 0, n = data.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && data[j] != '/') ++j;
            // j now points to the delimiter
            string lenStr = data.substr(i, j - i);
            size_t len = stoull(lenStr);   // length of the next string
            i = j + 1;                     // move past delimiter
            result.emplace_back(data.substr(i, len));
            i += len;                      // move to the start of the next length field
        }
        return result;
    }
};
