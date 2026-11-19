/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). Since the length consists only of digits, the separator can never be confused with the length itself, allowing us to parse the concatenated stream unambiguously even when the original strings contain any characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to a result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'/'` to obtain the length `len` of the next original string.
 * * Convert the collected digits to an integer, then extract the next `len` characters as the original string.
 * * Append the extracted string to the answer vector and continue until the whole encoded string is processed.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including delimiters).
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

#include <string>
#include <vector>
#include <cstddef>   // for size_t
#include <cstdlib>   // for std::stoi

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        // Reserve an approximate size to avoid many reallocations.
        size_t total_len = 0;
        for (const auto& s : strs) total_len += s.size() + 20; // extra for length and delimiter
        encoded.reserve(total_len);

        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';          // delimiter that never appears in the length part
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
            // Find the delimiter that ends the length field.
            size_t slashPos = i;
            while (slashPos < n && s[slashPos] != '/') ++slashPos;
            // Convert the length substring to an integer.
            int len = std::stoi(s.substr(i, slashPos - i));
            // Move index past the delimiter.
            i = slashPos + 1;
            // Extract the original string of length 'len'.
            result.emplace_back(s.substr(i, len));
            // Advance i to the start of the next encoded block.
            i += len;
        }
        return result;
    }
};
