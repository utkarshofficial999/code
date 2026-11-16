/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing its length and a special separator (e.g., ‘/’). The length tells us exactly how many characters belong to the original string, so any character—including the separator itself—can appear safely inside the payload.
 *
 * --- Approach ---
 * 1. **Encode**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter `'/'`, then `s` itself to the result string.
 * * The concatenated result is the encoded single string.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Locate the next delimiter `'/'` to obtain the length prefix.
 * * Convert the substring before the delimiter to an integer `len`.
 * * The next `len` characters form the original string; extract them and push into the answer vector.
 * * Move the cursor past the extracted part and repeat until the whole encoded string is processed.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → returns an empty string.
 * * Empty strings inside the vector are handled because their length (`0`) is stored.
 * * The delimiter may appear inside original strings; the length prefix disambiguates it.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the output string / vector (the algorithm uses only linear extra space).
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
#include <cstdlib>

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        encoded.reserve( (size_t)std::accumulate(strs.begin(), strs.end(), 0LL,
                                 [](long long sum, const std::string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reservation

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
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '/'
            size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            int len = std::stoi(s.substr(i, slashPos - i));
            i = slashPos + 1;                     // move past '/'
            result.emplace_back(s.substr(i, len)); // extract original string
            i += len;                             // move to next length prefix
        }
        return result;
    }
};
