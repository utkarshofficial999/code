/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself (e.g., ‘:’). While decoding we can read the length, skip the delimiter and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, then a delimiter `':'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each token, read characters until the delimiter `':'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations run in a single pass over the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character of the input strings is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_chars) – the encoded string (and the output vector for decoding) store all characters.
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
            encoded += ':';          // delimiter between length and content
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
            while (j < n && s[j] != ':') ++j;
            // safety: malformed input (should not happen in LeetCode tests)
            if (j == n) break;
            long long len = stoll(s.substr(i, j - i));
            i = j + 1; // skip ':'
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
