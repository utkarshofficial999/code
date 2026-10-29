/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator (e.g., ‘/’). The length tells us exactly where a string ends, so the original content (even if it contains ‘/’) never creates ambiguity. Decoding simply reads the length, skips the separator, and extracts that many characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to the result string.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * For each token, read characters until the delimiter `'/'` to obtain the length `len`.
 * * Convert the length substring to an integer.
 * * Extract the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter is placed **after** the length, never inside the length field, so the parser can always locate the separator.
 * * Because we use the exact length, any character (including `'/'`) inside the original string is safely preserved.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string in encode and for the resulting vector in decode (aside from the input).
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
#include <cstdlib>   // for std::stoll

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        // Reserve an approximate size to reduce reallocations.
        size_t total_len = 0;
        for (const auto& s : strs) total_len += s.size() + 20; // extra for length and delimiter
        encoded.reserve(total_len);

        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';
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
            // Extract length substring.
            std::string lenStr = s.substr(i, slashPos - i);
            // Convert to integer (use long long to be safe for huge strings).
            long long len = std::stoll(lenStr);
            // Move index past the delimiter.
            i = slashPos + 1;
            // Extract the actual string of length 'len'.
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            // Advance i past the extracted string.
            i += static_cast<size_t>(len);
        }
        return result;
    }
};
