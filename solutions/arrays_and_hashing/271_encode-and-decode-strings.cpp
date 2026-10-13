/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a separator that never appears in the length itself (a non‑digit character). During decoding we read the length, skip the separator, and extract exactly that many characters. This makes the process deterministic and works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, a delimiter `'/'`, and the string itself to the result.
 * - The delimiter is chosen because it is not a digit, so it can never be confused with the length field.
 * 
 * 2. **Decoding**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter `'/'` to obtain the length field. Convert it to an integer.
 * - Skip the delimiter and read exactly `len` characters – this is one original string.
 * - Continue until the whole encoded string is consumed.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encoded string is empty.
 * - Empty encoded string → decoded vector is empty.
 * - Strings may contain any characters (including `'/'`) because the length tells us exactly where each string ends.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output (encoded string or decoded vector). No extra auxiliary space beyond the output.
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
        encoded.reserve( // optional reservation to avoid many reallocations
            std::accumulate(strs.begin(), strs.end(), 0ULL,
                [](std::size_t sum, const std::string& s) { return sum + s.size() + 20; }));
        for (const std::string& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';          // delimiter that is not a digit
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        std::size_t i = 0;
        while (i < s.size()) {
            // find the delimiter that ends the length field
            std::size_t delimPos = i;
            while (delimPos < s.size() && s[delimPos] != '/')
                ++delimPos;
            // convert length substring to integer
            std::size_t len = static_cast<std::size_t>(std::stoll(s.substr(i, delimPos - i)));
            // move i past the delimiter
            i = delimPos + 1;
            // extract the original string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // advance to the start of the next encoded block
        }
        return result;
    }
};
