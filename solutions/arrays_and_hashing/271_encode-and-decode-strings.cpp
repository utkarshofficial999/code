/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator. Because the length is known before reading the actual characters, any character (including the separator) can safely appear inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, append `to_string(str.size())`, a delimiter (chosen as '`/`'), and then `str` itself to the result string.
 * * The delimiter is only used to locate where the length token ends; the actual string content is taken exactly `len` characters after it, so the delimiter may appear inside the string without ambiguity.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`/`' to obtain the length `len`.
 * * Convert the length token to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is consumed.
 * 
 * Both operations run in linear time with respect to the total number of characters processed.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the sum of lengths of all strings (including delimiters added during encoding).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
#include <stdexcept>

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        encoded.reserve(estimateSize(strs));
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
        std::size_t i = 0;
        const std::size_t n = s.size();

        while (i < n) {
            // Find delimiter to extract length
            std::size_t delimPos = s.find('/', i);
            if (delimPos == std::string::npos) {
                throw std::invalid_argument("Invalid encoded string");
            }

            // Parse length
            std::string lenStr = s.substr(i, delimPos - i);
            std::size_t len = static_cast<std::size_t>(std::stoll(lenStr));

            // Extract the actual string
            std::size_t start = delimPos + 1;
            if (start + len > n) {
                throw std::invalid_argument("Invalid encoded string");
            }
            result.emplace_back(s.substr(start, len));

            // Move index to the next encoded segment
            i = start + len;
        }
        return result;
    }

private:
    // Helper to reserve enough space for the encoded string (optional optimization)
    static std::size_t estimateSize(const std::vector<std::string>& strs) {
        std::size_t total = 0;
        for (const auto& s : strs) {
            total += std::to_string(s.size()).size(); // digits of length
            total += 1;                               // delimiter
            total += s.size();                         // actual characters
        }
        return total;
    }
};
