/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works even if the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * For every string `str` in the input vector, append `to_string(str.size())`, then a delimiter `'/'`, then the string itself to the result.
 * * Concatenating all such blocks yields a single encoded string.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'/'` – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string.
 * * Advance the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter is never part of the length field, so the boundary between length and data is unambiguous.
 * * Because we know the exact length of each original string, any characters (including `'/'`) inside the string are safely preserved.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / vector (the algorithm uses only a few auxiliary variables besides the required output).
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

/*
 * LeetCode 271 – Encode and Decode Strings
 * The codec uses length-prefixed encoding with '/' as a separator.
 */
class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve(estimateSize(strs));
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
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // sanity check – the input is guaranteed to be produced by encode()
            if (slashPos == string::npos) break;
            // length of the next string
            size_t len = stoull(s.substr(i, slashPos - i));
            // extract the string of that length
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));
            // move cursor forward
            i = start + len;
        }
        return result;
    }

private:
    // Helper to reserve enough space for the encoded string (optional optimisation)
    static size_t estimateSize(const vector<string>& strs) {
        size_t total = 0;
        for (const auto& s : strs) {
            total += s.size();                 // the string itself
            total += to_string(s.size()).size(); // length digits
            total += 1;                        // separator '/'
        }
        return total;
    }
};

/*
 * The platform expects a class named Solution; we simply expose the same
 * interface through inheritance to satisfy both possible signatures.
 */
class Solution : public Codec {
    // No extra code needed – inherits encode/decode.
};
