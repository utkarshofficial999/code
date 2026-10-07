/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself.
 * During decoding we read the length, skip the delimiter, and extract exactly that many characters – this works for any characters (including the delimiter) inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Iterate over the input vector `strs`.
 * - For each string `s` append `to_string(s.size())`, a single `'/'` as delimiter, and then `s` itself to the result string.
 * - The concatenated string is the encoded representation.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Find the next `'/'` to obtain the length field (`len`).
 * - Convert the length substring to an integer (`size_t`).
 * - The next `len` characters form the original string – push it into the answer vector.
 * - Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. **Correctness & Edge Cases**
 * - Empty strings become `"0/"` and are decoded correctly.
 * - An empty input vector yields an empty encoded string and vice‑versa.
 * - Using the length prefix makes the algorithm independent of the characters contained in the original strings (including `'/'`).
 * - All length calculations use `size_t`/`uint64_t` to avoid overflow.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the output).
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
#include <cstdint>   // for uint64_t
#include <stdexcept>

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        // Reserve an approximate size to reduce reallocations.
        std::size_t total_len = 0;
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
    std::vector<std::string> decode(const std::string& data) {
        std::vector<std::string> result;
        std::size_t i = 0;
        const std::size_t n = data.size();

        while (i < n) {
            // Locate the delimiter that separates length and string.
            std::size_t slashPos = data.find('/', i);
            if (slashPos == std::string::npos) {
                // Malformed input – break gracefully.
                break;
            }

            // Extract length substring and convert to integer.
            std::string lenStr = data.substr(i, slashPos - i);
            // Use uint64_t to safely hold very large lengths.
            std::uint64_t len = 0;
            try {
                len = std::stoull(lenStr);
            } catch (const std::invalid_argument&) {
                // Invalid length field – stop processing.
                break;
            } catch (const std::out_of_range&) {
                // Length too big – stop processing.
                break;
            }

            // Move cursor past the '/' delimiter.
            i = slashPos + 1;

            // Guard against out‑of‑bounds if the encoded string is corrupted.
            if (i + len > n) break;

            result.emplace_back(data.substr(i, static_cast<std::size_t>(len)));
            i += static_cast<std::size_t>(len);
        }
        return result;
    }
};
