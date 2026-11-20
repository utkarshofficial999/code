/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears in the numeric length. While decoding we can read the length, skip the separator and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a delimiter (e.g., '`/`'), and then `s` itself to the result string.
 * * The delimiter is safe because the length part consists only of digits, so '`/`' can never be confused with a digit.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each segment, read characters until the delimiter '`/`' to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the added length fields).
 * Space Complexity: O(N) for the encoded string and the decoded vector.
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
#include <cstddef>

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        // Reserve an approximate size to reduce reallocations
        size_t total_len = 0;
        for (const auto& s : strs) total_len += s.size() + 10; // extra for length and delimiter
        encoded.reserve(total_len);

        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';               // delimiter
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        size_t i = 0;
        const size_t n = s.size();

        while (i < n) {
            // Find the delimiter that ends the length field
            size_t slashPos = s.find('/', i);
            // The problem guarantees a valid encoding, so slashPos will be found
            std::string lenStr = s.substr(i, slashPos - i);
            size_t len = std::stoull(lenStr);   // convert length to integer

            // Extract the actual string of length 'len'
            size_t start = slashPos + 1;
            result.emplace_back(s.substr(start, len));

            // Move i to the beginning of the next encoded segment
            i = start + len;
        }
        return result;
    }
};
