/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). Because the length is written in decimal, the separator can never be confused with the length itself, allowing us to recover the original strings unambiguously even if they contain any characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a separator `'/'`, then `s` itself to the result string.
 * * The concatenated result is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the separator `'/'` – this gives the length `len` of the next original string.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * Both operations touch each character exactly once, giving linear time.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the added length fields).
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
            // find the separator '/'
            size_t slash = s.find('/', i);
            // safety check – malformed input (should not happen in LeetCode)
            if (slash == string::npos) break;

            // length of the next string
            size_t len = stoull(s.substr(i, slash - i));
            i = slash + 1; // move past '/'

            // extract the string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next length field
        }
        return result;
    }
};
