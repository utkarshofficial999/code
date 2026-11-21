/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string with its length followed by a special separator. Because the length tells us exactly how many characters belong to the original string, the separator can appear inside the string without causing ambiguity.
 *
 * --- Approach ---
 * 1. **Encode**
 * * For every string `str` in the input vector, append `to_string(str.size())`, a delimiter (choose `'/'`), and then `str` itself to the result string.
 * * The final concatenated string represents the whole list.
 * 
 * 2. **Decode**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'/'` – this substring is the length `len` of the next original string.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and store it.
 * * Continue until the end of the encoded string.
 * 
 * Both operations run in linear time with respect to the total number of characters.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters in all strings combined (including delimiters).
 * Space Complexity: O(N) for the encoded string and the vector produced by decode.
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
#include <cstdlib>   // for std::stoll
#include <cstddef>   // for std::size_t

class Solution {
public:
    // Encodes a list of strings to a single string.
    std::string encode(const std::vector<std::string>& strs) {
        std::string encoded;
        encoded.reserve( (size_t)strs.size() * 5 ); // small reservation, grows as needed
        for (const auto& s : strs) {
            encoded += std::to_string(s.size());
            encoded += '/';          // delimiter that never appears in the length part
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(const std::string& s) {
        std::vector<std::string> result;
        std::size_t i = 0;
        while (i < s.size()) {
            // find delimiter '/'
            std::size_t delimPos = s.find('/', i);
            // safety check – malformed input would break here
            if (delimPos == std::string::npos) break;

            // length substring [i, delimPos)
            std::string lenStr = s.substr(i, delimPos - i);
            long long len = std::stoll(lenStr);   // length fits in long long

            // extract the actual string
            std::size_t start = delimPos + 1;
            std::string word = s.substr(start, static_cast<std::size_t>(len));
            result.push_back(std::move(word));

            // move index past the extracted word
            i = start + static_cast<std::size_t>(len);
        }
        return result;
    }
};
