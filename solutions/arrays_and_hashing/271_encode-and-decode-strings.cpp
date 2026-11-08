/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length followed by a special separator (e.g., ‘/’). Because the length is written in decimal, the separator never appears inside the numeric prefix, so decoding can reliably split the stream back into the original strings, even if the strings themselves contain any characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then the string itself to a result `std::string`.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert the length substring to an integer.
 * * Extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the end of the encoded string.
 * 
 * Both steps run in linear time with respect to the total number of characters processed.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the length prefixes and delimiters).
 * Space Complexity: O(N) for the encoded string and the vector returned by decode.
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
 * LeetCode 271. Encode and Decode Strings
 * Design a codec to encode a list of strings to a single string and decode it back.
 *
 * The implementation uses length-prefixed encoding with '/' as a delimiter.
 */

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve(strs.size() * 10); // rough reservation to reduce reallocations
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
        size_t i = 0;
        const size_t n = s.size();

        while (i < n) {
            // Find the delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // Defensive check – the input is guaranteed to be well‑formed by encode()
            if (slashPos == string::npos) break;

            // Extract length
            size_t len = 0;
            // manual conversion to avoid stoi overhead on huge inputs
            for (size_t j = i; j < slashPos; ++j) {
                len = len * 10 + (s[j] - '0');
            }

            // Extract the actual string of length 'len'
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // Move index past the processed part
            i = start + len;
        }
        return result;
    }
};

/*
 * The class can be used as follows (LeetCode driver code):
 *
 * Codec codec;
 * string encoded = codec.encode(strs);
 * vector<string> decoded = codec.decode(encoded);
 *
 * The decoded vector will be identical to the original `strs`.
 */
