/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’). The separator guarantees that the decoder knows exactly where the length ends, so any characters inside the original strings (including digits or ‘/’) do not interfere.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, append `to_string(str.size())`, then a separator `'/'`, then the string itself to the result.
 * * The final concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next separator `'/'` to obtain the length field. Convert this substring to an integer `len`.
 * * The next `len` characters form the original string; push it into the answer vector.
 * * Move the cursor past the extracted string and repeat until the end of the encoded data.
 * 
 * Both operations run in linear time with respect to the total number of characters processed.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including the added length fields).
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
        encoded.reserve( (size_t)1e5 ); // optional reserve for large inputs
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';          // separator that never appears in the length field
            encoded += s;            // the actual string (may be empty)
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        size_t i = 0;
        const size_t n = s.size();

        while (i < n) {
            // Find the separator that ends the length field
            size_t slashPos = s.find('/', i);
            // Extract length substring and convert to integer
            long long len = std::stoll(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move past the separator
            // Extract the original string of length 'len'
            result.emplace_back(s.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);  // move to the start of the next encoded block
        }
        return result;
    }
};
