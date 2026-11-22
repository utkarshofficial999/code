/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a separator that cannot appear in the length representation (e.g., ‘/’). During decoding we read the length, skip the separator, and extract exactly that many characters. The length prefix guarantees correctness even if the original strings contain any possible characters.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, then a single separator `'/'`, then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each segment, read characters until the separator `'/'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both operations touch each character exactly once.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the added length prefixes).
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
        for (const auto& s : strs) total_len += s.size() + 20; // extra for length and separator
        encoded.reserve(total_len);

        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';          // separator that never appears in the numeric length
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
            // Find the separator to extract the length.
            size_t sep = i;
            while (sep < n && s[sep] != '/') ++sep;
            // Convert substring [i, sep) to integer length.
            std::string len_str = s.substr(i, sep - i);
            long long len = std::stoll(len_str);   // safe for large lengths
            // Move index past the separator.
            i = sep + 1;
            // Extract the original string of length 'len'.
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);
        }
        return result;
    }
};
