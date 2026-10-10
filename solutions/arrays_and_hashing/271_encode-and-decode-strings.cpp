/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘#’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – the separator never appears in the length field, so the original content (even if it contains ‘#’) is recovered safely.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `s` in the input vector:
 * – Append `to_string(s.size())`, then a delimiter `'#'`, then the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'#'` to obtain the length `len` of the next original string.
 * * Convert the length substring to an integer (`stoll`).
 * * The original string occupies the next `len` characters; extract it and push it into the answer vector.
 * * Move the scanning index past the extracted part and repeat until the end of the encoded string.
 * 
 * 3. **Correctness for Edge Cases**
 * * Empty input vector → encoded string is empty, decoding returns an empty vector.
 * * Empty strings inside the vector → encoded as `"0#"`; decoding reads length 0 and correctly produces an empty string.
 * * Strings may contain any character, including ‘#’, because we never rely on the delimiter after the length field.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encoding and decoding).
 * Space Complexity: O(N) for the output of both functions (the encoded string or the decoded vector).
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
            // find delimiter '#'
            size_t delim = s.find('#', i);
            // safety check (should never happen for valid input)
            if (delim == string::npos) break;

            // length of the next string
            long long len = stoll(s.substr(i, delim - i));
            i = delim + 1; // move past '#'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, (size_t)len));
            i += (size_t)len;
        }
        return result;
    }
};
