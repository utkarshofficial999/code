/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. During decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a special delimiter (e.g., `'#'`), then `s` itself to the result string.
 * * The delimiter is safe because the length is represented only by digits, never by `'#'`.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'#'` – this substring is the decimal representation of the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted string and repeat until the end of the encoded string.
 * 
 * 3. **Correctness & Edge Cases**
 * * Empty strings are encoded as `"0#"` and decoded correctly.
 * * Strings may contain any character (including `'#'`) because the delimiter is only examined **after** the length field, not inside the payload.
 * * Use `size_t` (or `uint64_t`) for lengths to avoid overflow; the total length of the encoded string fits in memory because it is exactly the sum of all input characters plus O(N) extra characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(total_chars) – each character of the input is visited a constant number of times during encoding and decoding.
 * Space Complexity: O(total_chars) – the encoded string stores all original characters plus a small constant overhead per string.
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
                                            [](size_t sum, const string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reserve

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';               // delimiter
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
            while (j < n && s[j] != '#') ++j;
            // j now points to delimiter
            string lenStr = s.substr(i, j - i);
            size_t len = stoull(lenStr); // safe conversion, works for large lengths
            i = j + 1;                    // skip delimiter

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len;                     // move to the start of next encoded block
        }
        return result;
    }
};
