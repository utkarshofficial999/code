/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself. During decoding we can read the length, skip the delimiter, and extract exactly that many characters – guaranteeing a loss‑less round‑trip even when the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty `std::string ans`.
 * * For every string `s` in the input vector:
 * – Append `std::to_string(s.size())` (the length).
 * – Append a single delimiter character, e.g. `'/'`.
 * – Append the string `s` itself.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment:
 * – Locate the next delimiter `'/'` to obtain the length substring.
 * – Convert this substring to an integer `len`.
 * – The actual string starts right after the delimiter and spans `len` characters.
 * – Extract it with `substr` and push it into the answer vector.
 * – Move the cursor past the extracted part and repeat until the end of the encoded string.
 * 
 * 3. The delimiter `'/'` is safe because it never appears inside the numeric length representation, so the parsing is unambiguous.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character a constant number of times).
 * Space Complexity: O(N) for the output string / vector (aside from the input).
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
            encoded += '/';          // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> decoded;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter that separates length and string
            size_t slash = s.find('/', i);
            // safety: if not found, malformed input – break
            if (slash == string::npos) break;
            // length substring [i, slash)
            size_t len = stoull(s.substr(i, slash - i));
            // actual string starts after the slash
            size_t start = slash + 1;
            decoded.emplace_back(s.substr(start, len));
            i = start + len; // move to next encoded block
        }
        return decoded;
    }
};
