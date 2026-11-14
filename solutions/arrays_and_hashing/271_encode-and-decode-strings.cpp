/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a delimiter that never appears in the length representation. During decoding we can read the length, skip the delimiter, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `t` append `to_string(t.size())`, a special delimiter (e.g., '`/`'), and then `t` itself to the result string.
 * * The delimiter is safe because the length part consists only of digits.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter '`/`' – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as one original string.
 * * Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → returns an empty string.
 * * Empty strings inside the vector are encoded as `"0/"` and correctly decoded.
 * * The algorithm works for any characters (including delimiters) inside the original strings because the delimiter separates the length from the content, not the content itself.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (each character is processed a constant number of times).
 * Space Complexity: O(N) for the encoded string (and the output vector during decoding).
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
        encoded.reserve( (size_t)1e6 ); // optional reservation for speed
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';               // delimiter between length and string
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
            // find delimiter '/'
            size_t slashPos = i;
            while (slashPos < n && s[slashPos] != '/') ++slashPos;
            // substring [i, slashPos) is the length
            std::string lenStr = s.substr(i, slashPos - i);
            size_t len = static_cast<size_t>(std::stoul(lenStr));

            // move past the delimiter
            i = slashPos + 1;
            // extract the actual string of length 'len'
            result.emplace_back(s.substr(i, len));
            i += len; // advance to the start of the next encoded block
        }
        return result;
    }
};
