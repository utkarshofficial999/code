/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length itself. While decoding we can read the length up to the delimiter, then extract exactly that many characters – this works for any possible characters inside the original strings, including the delimiter.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, a special delimiter (e.g., `'#'`), and then `s` itself to the result string.
 * * Return the concatenated result.
 * 
 * 2. **Decode**
 * * Scan the encoded string `s` from left to right.
 * * For each segment, read characters until the delimiter `'#'` to obtain the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Continue until the whole encoded string is processed.
 * 
 * Both functions run in linear time with respect to the total number of characters and use only O(1) extra auxiliary space besides the output containers.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined.
 * Space Complexity: O(N) for the output (the encoded string or the decoded vector). No additional asymptotic space is used.
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
#include <cstdlib>   // for std::stoul

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '#';          // delimiter that separates length from data
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> decoded;
        std::size_t i = 0;
        while (i < s.size()) {
            // find delimiter '#'
            std::size_t delimPos = s.find('#', i);
            // length substring is [i, delimPos)
            std::size_t len = std::stoul(s.substr(i, delimPos - i));
            // actual string starts after the delimiter
            std::size_t start = delimPos + 1;
            decoded.emplace_back(s.substr(start, len));
            i = start + len; // move to the next encoded block
        }
        return decoded;
    }
};
