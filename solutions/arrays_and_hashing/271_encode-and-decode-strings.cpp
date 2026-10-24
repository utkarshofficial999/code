/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation (e.g., ‘/’). While decoding we read the length, skip the delimiter, and then extract exactly that many characters. This makes the process deterministic even when the original strings contain any possible characters, including the delimiter itself.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Initialise an empty result string.
 * * For every string `s` in the input vector:
 * - Append `to_string(s.size())` (the length).
 * - Append a single delimiter character `'/'`.
 * - Append the string `s` itself.
 * * Return the concatenated result.
 * * An empty vector yields an empty string.
 * 
 * 2. **Decode**
 * * Initialise an empty vector `ans`.
 * * Scan the encoded string with an index `i`.
 * * While `i` is less than the string size:
 * - Read characters from `i` until the delimiter `'/'` to obtain the length `len`.
 * - Convert the collected substring to an integer (`size_t`).
 * - Move `i` past the delimiter.
 * - Extract the next `len` characters as the original string and push it into `ans`.
 * - Advance `i` by `len`.
 * * If the encoded string is empty, return an empty vector.
 * 
 * 3. **Correctness Guarantees**
 * * The delimiter separates the length from the payload, so the parser never confuses characters belonging to the original string with the length field.
 * * Using the exact length ensures that any characters (including `'/'`) inside the original string are reproduced faithfully.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (including the added length fields). Both encoding and decoding scan each character a constant number of times.
 * Space Complexity: O(N) for the output string in encode and for the resulting vector in decode. Only O(1) auxiliary space is used besides the output.
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
#include <cstdlib>   // for std::stoull

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        encoded.reserve(strs.size() * 5); // rough reservation, grows as needed
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';               // delimiter separating length and data
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> decoded;
        std::size_t i = 0;
        const std::size_t n = s.size();

        while (i < n) {
            // Find delimiter to extract length
            std::size_t delimPos = i;
            while (delimPos < n && s[delimPos] != '/') ++delimPos;
            // Convert length substring to integer
            std::size_t len = 0;
            if (delimPos > i) {
                // Using stoull for safety with large lengths
                len = static_cast<std::size_t>(std::stoull(s.substr(i, delimPos - i)));
            }
            // Move index past delimiter
            i = delimPos + 1;
            // Extract the original string of length 'len'
            decoded.emplace_back(s.substr(i, len));
            i += len;
        }
        return decoded;
    }
};
