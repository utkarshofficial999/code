/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length followed by a unique separator (e.g., ‘/’). The separator never appears inside the length field, so during decoding we can read the length, skip the separator, and extract exactly that many characters for the original string.
 *
 * --- Approach ---
 * 1. **Encode**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then the string itself to the result.
 * - The concatenated result is returned as the encoded single string.
 * 
 * 2. **Decode**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter `'/'` to obtain the length of the upcoming original string.
 * - Convert the length substring to an integer, then read exactly that many characters after the delimiter as the original string.
 * - Append the recovered string to the answer vector and continue until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * - Strings may contain any characters (including `'/'`) because the delimiter is only used **outside** the length field.
 *
 * --- Complexity ---
 * Time Complexity:  O(total length of all strings) for both encode and decode.
 * Space Complexity: O(total length of all strings) for the output (the encoded string or the decoded vector).
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
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& data) {
        vector<string> result;
        size_t i = 0, n = data.size();

        while (i < n) {
            // find delimiter that separates length and string
            size_t slashPos = data.find('/', i);
            // length substring is [i, slashPos)
            int len = stoi(data.substr(i, slashPos - i));
            i = slashPos + 1; // move past '/'

            // extract the original string of length 'len'
            result.emplace_back(data.substr(i, len));
            i += len; // move to the start of the next length field
        }
        return result;
    }
};
