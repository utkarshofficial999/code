/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator (e.g., ‘/’).
 * During decoding we read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a separator `'/'`, then `s` itself to the result string.
 * * The concatenated string is returned.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Find the next separator `'/'` to obtain the length field.
 * * Convert the length substring to an integer (`size_t`).
 * * The next `len` characters form the original string – push it into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge‑case handling**
 * * Empty input vector → encoded string is empty.
 * * Empty encoded string → decoded vector is empty.
 * * The separator never appears inside the length field, so any characters (including `'/'`) inside the original strings are safely preserved.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is visited a constant number of times).
 * Space Complexity: O(N) for the output string / vector (no extra auxiliary storage beyond the result).
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
        encoded.reserve( // optional reservation to avoid many reallocations
            std::accumulate(strs.begin(), strs.end(), 0ULL,
                [](unsigned long long sum, const std::string& s) {
                    return sum + s.size() + 20; // extra space for length and separator
                })
        );

        for (const std::string& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        std::size_t i = 0;
        while (i < s.size()) {
            // locate separator that ends the length field
            std::size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            std::size_t len = static_cast<std::size_t>(std::stoull(s.substr(i, slashPos - i)));
            i = slashPos + 1;                     // move past the separator
            result.emplace_back(s.substr(i, len)); // extract the original string
            i += len;                             // advance to the start of next length field
        }
        return result;
    }
};
