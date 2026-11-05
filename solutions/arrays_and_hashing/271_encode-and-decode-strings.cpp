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
 * During decoding we can read the length, skip the separator and extract exactly that many characters – no character in the original strings can break the parsing.
 *
 * --- Approach ---
 * 1. **Encoding** (`string encode(const vector<string>& strs)`)
 * * Initialise an empty result string.
 * * For every string `s` in `strs` append
 * `to_string(s.size()) + '/' + s`
 * (`'/'` is the separator because it never appears in the numeric length).
 * * Return the concatenated result.
 * 
 * 2. **Decoding** (`vector<string> decode(const string& s)`)
 * * Scan the encoded string from left to right.
 * * Find the next `'/'` – the substring before it is the length `len`.
 * * Convert `len` to an integer (`size_t`).
 * * The next `len` characters after the separator form the original string; push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole string is processed.
 * 
 * 3. Handle corner cases automatically:
 * * Empty input vector → empty encoded string.
 * * Empty strings inside the vector → encoded as `"0/"` and correctly decoded.
 * * Very long strings → use `size_t`/`uint64_t` for length to avoid overflow.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (each character is visited a constant number of times).
 * Space Complexity: O(N) for the output of encode and for the vector returned by decode.
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
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), (size_t)0,
                                            [](size_t acc, const string& s){ return acc + s.size(); })
                         + strs.size() * 5 ); // rough reservation

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
            // locate separator
            size_t slashPos = s.find('/', i);
            // slash must exist in a valid encoding
            if (slashPos == string::npos) break; // malformed input, safeguard

            // length substring
            string lenStr = s.substr(i, slashPos - i);
            // convert to integer (use unsigned long long to be safe)
            size_t len = stoull(lenStr);

            // extract the actual string
            size_t start = slashPos + 1;
            string cur = s.substr(start, len);
            result.push_back(std::move(cur));

            // move cursor forward
            i = start + len;
        }
        return result;
    }
};
