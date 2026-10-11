/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a non‑numeric separator. While decoding we first read the length up to the separator, then extract exactly that many characters – the separator itself never appears in the length field, so the original content (even if it contains the separator) is recovered safely.
 *
 * --- Approach ---
 * 1. **Encode**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, a delimiter `':'`, and the string itself to the result.
 * - The final concatenated string is returned.
 * 
 * 2. **Decode**
 * - Scan the encoded string from left to right.
 * - Locate the next delimiter `':'` to obtain the length of the upcoming original string.
 * - Convert the length substring to an integer (`stoll` to avoid overflow).
 * - Extract the next `len` characters as the original string and push it into the answer vector.
 * - Move the cursor past the extracted part and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * - Empty input vector → encoded string is empty.
 * - Empty encoded string → decoded vector is empty.
 * - Strings may contain any characters, including the delimiter; because we read a fixed number of characters after the delimiter, the content is preserved.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is processed a constant number of times).
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

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), 0LL,
                                            [](long long sum, const string& s){ return sum + s.size(); })
                         + strs.size() * 5 ); // rough reserve to avoid many reallocations
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += ':';          // delimiter that is not a digit
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();
        while (i < n) {
            // find delimiter
            size_t j = i;
            while (j < n && s[j] != ':') ++j;
            // length substring [i, j)
            long long len = stoll(s.substr(i, j - i));
            // extract the string of length 'len' after the delimiter
            string word = s.substr(j + 1, static_cast<size_t>(len));
            result.push_back(std::move(word));
            i = j + 1 + static_cast<size_t>(len);
        }
        return result;
    }
};
