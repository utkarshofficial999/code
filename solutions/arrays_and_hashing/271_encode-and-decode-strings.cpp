/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator that never appears in the length itself. During decoding we can read the length, skip the separator, and extract exactly that many characters – this works for any possible characters inside the original strings, including empty strings.
 *
 * --- Approach ---
 * 1. **Encoding**
 * * Iterate over the input vector `strs`.
 * * For each string `s`, append `to_string(s.size())`, then a delimiter (choose `'#'`), then `s` itself to the result string.
 * * The delimiter is safe because it never occurs inside the numeric length representation.
 * 
 * 2. **Decoding**
 * * Scan the encoded string from left to right.
 * * Read characters until the delimiter `'#'` is found – this substring is the length `len`.
 * * Convert `len` to an integer, then take the next `len` characters as the original string and push it into the answer vector.
 * * Move the cursor past the extracted string and repeat until the end of the encoded string.
 * 
 * 3. **Edge Cases**
 * * Empty input vector → encode returns an empty string; decode of an empty string returns an empty vector.
 * * Empty strings inside the vector are correctly encoded as `"0#"` and decoded back to `""`.
 * * All characters (including `'#'`) are allowed inside the original strings because we never rely on the delimiter appearing inside the string itself – we only look for the delimiter after the length field.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (each character is processed a constant number of times).
 * Space Complexity: O(N) for the encoded string and the output vector during decoding.
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
                         + strs.size()*5 ); // rough reservation

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '#';          // delimiter between length and content
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0, n = s.size();

        while (i < n) {
            // find delimiter '#'
            size_t j = i;
            while (j < n && s[j] != '#') ++j;
            // substring [i, j) is the length
            size_t len = stoull(s.substr(i, j - i));
            // move past '#'
            i = j + 1;
            // extract the original string of length len
            result.emplace_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
};
