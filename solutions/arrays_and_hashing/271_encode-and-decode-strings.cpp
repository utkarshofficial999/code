/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘:’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works even when the original strings contain any possible characters, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `':'`, then `s` itself to the result string.
 * * The concatenated result is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token, read characters until the delimiter `':'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both steps run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the output vector (the algorithm uses only a few auxiliary variables).
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

#include <string>
#include <vector>
#include <cstddef>   // for size_t
#include <stdexcept> // for std::invalid_argument

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += ':';               // delimiter that never appears in the length field
            encoded += s;                 // the actual string (may be empty)
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        std::size_t i = 0;
        const std::size_t n = s.size();

        while (i < n) {
            // read the length prefix
            std::size_t len = 0;
            while (i < n && s[i] != ':') {
                if (s[i] < '0' || s[i] > '9') {
                    throw std::invalid_argument("Invalid encoded string");
                }
                len = len * 10 + (s[i] - '0');
                ++i;
            }
            // skip the delimiter ':'
            ++i; // now i points to the first character of the actual string

            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // move to the start of the next length field
        }
        return result;
    }
};
