/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Encode and Decode Strings (LeetCode #271)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/encode-and-decode-strings/
 * NeetCode URL: https://neetcode.io/problems/string-encode-and-decode?list=neetcode250
 * Status: Submission Failed (HTTP 403) (Runtime: N/A, Memory: N/A)
 *
 * --- Intuition ---
 * Encode each string by prefixing it with its length and a special separator.
 * During decoding we read the length up to the separator, then extract exactly that many characters – this works for any possible characters inside the original strings (including the separator itself).
 *
 * --- Approach ---
 * 1. **Encode**
 * - Iterate over the input vector `strs`.
 * - For each string `s`, append `to_string(s.size())`, a delimiter `'/'`, and the string itself to the result.
 * - The delimiter is safe because the length tells us exactly where the original string ends, even if the string contains `'/'`.
 * 
 * 2. **Decode**
 * - Scan the encoded string from left to right.
 * - Find the next delimiter `'/'` to obtain the length of the next original string.
 * - Convert the length substring to an integer (`size_t`).
 * - Take the following `len` characters as the original string, push it into the answer vector, and advance the cursor past those characters.
 * - Repeat until the whole encoded string is consumed.
 * 
 * 3. Handle corner cases automatically:
 * - Empty input vector → encoded string is empty, decoding yields an empty vector.
 * - Empty strings inside the vector → encoded as `"0/"` and decoded back to `""`.
 *
 * --- Complexity ---
 * Time Complexity:  O(N) where N is the total number of characters across all strings (both encoding and decoding scan each character once).
 * Space Complexity: O(N) for the encoded string and the output vector (no extra auxiliary structures beyond the result).
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

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(const vector<string>& strs) {
        string encoded;
        encoded.reserve( (size_t)accumulate(strs.begin(), strs.end(), (size_t)0,
                                            [](size_t sum, const string& s){ return sum + s.size(); })
                         + strs.size()*5 ); // rough reservation
        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += '/';
            encoded += s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(const string& s) {
        vector<string> result;
        size_t i = 0;
        while (i < s.size()) {
            // locate delimiter
            size_t slashPos = s.find('/', i);
            // length substring is [i, slashPos)
            size_t len = stoull(s.substr(i, slashPos - i));
            i = slashPos + 1;               // move past delimiter
            result.emplace_back(s.substr(i, len));
            i += len;                       // skip the extracted string
        }
        return result;
    }
};

/*
The class can be used as follows (LeetCode harness does it automatically):

Codec codec;
string encoded = codec.encode({"Hello","World"});
vector<string> decoded = codec.decode(encoded);
*/
