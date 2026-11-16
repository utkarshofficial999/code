/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator.
 * During decoding we read the length, skip the separator, and extract exactly that many characters – the separator never appears inside the length field, so the process is unambiguous even if the original strings contain any characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (e.g., `'#'`), and then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'#'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → returns an empty string.
 * * Empty strings inside the vector are encoded as `"0#"` and decoded correctly.
 * * The algorithm works for any characters (including the delimiter) inside the original strings because the delimiter is only used **outside** the length field.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / decoded vector (aside from the input).
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
        encoded.reserve( (size_t) accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';               // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();

        while (i < n) {
            // read length
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr);   // length of the next original string
            i = j + 1;                     // move past '#'

            decoded.emplace_back(s.substr(i, len));
            i += len;                      // move to the start of next length field
        }
        return decoded;
    }
};
