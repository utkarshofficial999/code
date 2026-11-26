/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation (e.g., ‘#’). During decoding we can read the length up to the delimiter, then extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'#'`, then the string itself to the result.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * Locate the next delimiter `'#'` to obtain the length of the next original string.
 * * Convert the substring before `'#'` to an integer (`size_t`).
 * * Extract the next `len` characters as the original string, push it into the answer vector, and move the cursor past those characters.
 * * Repeat until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty.
 * * Empty strings inside the vector → encoded as `"0#"` (length 0, no characters follow).
 * * Very long strings → use `size_t`/`unsigned long long` for length conversion to avoid overflow.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encode and decode scan each character once).
 * Space Complexity: O(N) for the output string / vector (aside from the input).
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
        encoded.reserve(estimateSize(strs));   // optional reservation for speed
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '#';
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
            // Find delimiter '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // Convert length substring to integer
            unsigned long long len = std::stoull(s.substr(i, j - i));
            i = j + 1; // move past '#'
            // Extract the original string of length 'len'
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);
        }
        return result;
    }

private:
    // Helper to roughly estimate needed capacity for the encoded string.
    static size_t estimateSize(const std::vector<std::string>& strs) {
        size_t total = 0;
        for (const auto& s : strs) {
            // digits of length + 1 delimiter + actual characters
            total += numDigits(s.size()) + 1 + s.size();
        }
        return total;
    }

    static size_t numDigits(size_t x) {
        if (x == 0) return 1;
        size_t cnt = 0;
        while (x) {
            ++cnt;
            x /= 10;
        }
        return cnt;
    }
};
