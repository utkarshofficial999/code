/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Store each string together with its length. By prefixing a string with its length and a non‑numeric delimiter we can uniquely split the concatenated result, even when the original strings contain any characters (including the delimiter itself).
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, compute its length `len`.
 * * Append `len`, a special delimiter (e.g., `'#'`), and then `str` itself to a result string.
 * * The final concatenated string is the encoding.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'#'`; the characters before it form the decimal representation of the length `len`.
 * * Convert this substring to an integer, then read the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * Both steps run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string (output) and O(N) for the decoded vector (input), i.e., linear auxiliary space.
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

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                         [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter that never appears in the length field
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '#'
            size_t delim = s.find('#', i);
            // safety check (should never happen for a valid encoding)
            if (delim == string::npos) break;

            // length of the next string
            size_t len = stoull(s.substr(i, delim - i));

            // extract the string of length 'len' after the delimiter
            size_t start = delim + 1;
            result.emplace_back(s.substr(start, len));

            // move cursor forward
            i = start + len;
        }
        return result;
    }
};

/*
The LeetCode platform expects the class name to be Codec with the two
public methods encode and decode as defined above.
*/
