/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length first, then the raw characters. By storing the length in a fixed‑size (4‑byte) binary header we never need a special delimiter, so any character (including ‘#’, ‘/’, etc.) inside the original strings is safe.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector:
 * * Compute its length `len` (as a 32‑bit unsigned integer).
 * * Append the 4 bytes of `len` in big‑endian order to the result string.
 * * Append the characters of `str` itself.
 * * The final encoded string is the concatenation of all these blocks.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read the next 4 bytes, reconstruct the original length `len`.
 * * Extract the following `len` characters as one decoded string and push it into the answer vector.
 * * Repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → returns an empty string.
 * * Empty strings inside the vector are encoded as a 4‑byte zero length followed by nothing, and decoded correctly.
 * * The algorithm works for any string content because no delimiter is used.
 * * Lengths larger than `2³²‑1` cannot be represented; the problem constraints guarantee total size fits in memory, so a 32‑bit length is sufficient.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is read/written once).
 * Space Complexity: O(N) for the encoded string plus O(N) for the decoded vector (output space).
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
    // Encode a list of strings to a single string.
    string encode(vector<string>& strs) {
        string encoded;
        encoded.reserve(strs.size() * 5); // rough reservation

        for (const string& s : strs) {
            uint32_t len = static_cast<uint32_t>(s.size());
            // store length in big‑endian order (most significant byte first)
            for (int i = 3; i >= 0; --i) {
                encoded.push_back(static_cast<char>((len >> (i * 8)) & 0xFF));
            }
            encoded.append(s);
        }
        return encoded;
    }

    // Decode a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> result;
        size_t i = 0;
        const size_t n = s.size();

        while (i + 4 <= n) {               // need at least 4 bytes for length
            uint32_t len = 0;
            for (int j = 0; j < 4; ++j) {
                len = (len << 8) | static_cast<unsigned char>(s[i + j]);
            }
            i += 4;
            // safety check – if the encoded string is malformed we break
            if (i + len > n) break;
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
