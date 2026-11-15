/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a fixed non‑numeric separator.
 * During decoding we read the length, skip the separator, and then take exactly that many characters – this works for any possible characters inside the original strings, including the separator itself.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s` append `to_string(s.size())`, a delimiter (e.g. '`/`'), and then `s` itself to the result string.
 * * The delimiter is chosen to be a character that never appears in the numeric length, so parsing is unambiguous.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Find the next delimiter '`/`' – the substring before it is the length `len`.
 * * Convert `len` to an integer (`size_t`).
 * * The next `len` characters form the original string; push it into the answer vector.
 * * Move the cursor past those `len` characters and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encoded string is empty.
 * * Empty strings inside the vector are encoded as "`0/`" and decoded correctly.
 * * Very long strings are handled because we use `size_t` (64‑bit on modern platforms) and never rely on fixed buffers.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times during encode and decode).
 * Space Complexity: O(N) for the output of encode and for the vector returned by decode (the algorithm itself uses only O(1) auxiliary space).
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
#include <cstdlib>   // for stoull

class Solution {
public:
    // Encode a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        encoded.reserve( /* optional reservation */ );
        for (const std::string& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';               // delimiter that never appears in the length
            encoded += s;
        }
        return encoded;
    }

    // Decode a single string back to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        std::size_t i = 0;
        while (i < s.size()) {
            // locate delimiter that separates length and the actual string
            std::size_t delimPos = s.find('/', i);
            // length substring is [i, delimPos)
            std::size_t len = std::stoull(s.substr(i, delimPos - i));
            i = delimPos + 1;                     // move past delimiter
            result.emplace_back(s.substr(i, len));
            i += len;                             // skip the extracted string
        }
        return result;
    }
};
