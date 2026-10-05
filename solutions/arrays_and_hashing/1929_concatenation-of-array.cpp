/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Concatenation of Array (LeetCode #1929)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/concatenation-of-array/
 * NeetCode URL: https://neetcode.io/problems/concatenation-of-array?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 16.8 MB)
 *
 * --- Intuition ---
 * The required array is simply the original array written twice in a row.
 * So we just need to copy each element of `nums` to two positions: its original index and the same index shifted by `n`.
 *
 * --- Approach ---
 * 1. Let `n = nums.size()`.
 * 2. Create a result vector `ans` of size `2 * n`.
 * 3. Iterate `i` from `0` to `n‑1`:
 * * Set `ans[i] = nums[i]` (first copy).
 * * Set `ans[i + n] = nums[i]` (second copy).
 * 4. Return `ans`.
 *
 * --- Complexity ---
 * Time Complexity:  ** `O(n)` – one linear pass over the input.
 * Space Complexity: ** `O(n)` – the output vector of size `2n` (the extra factor of 2 is constant).
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

#include <vector>

class Solution {
public:
    std::vector<int> getConcatenation(std::vector<int>& nums) {
        const std::size_t n = nums.size();          // original length
        std::vector<int> ans(2 * n);                // allocate result

        for (std::size_t i = 0; i < n; ++i) {
            ans[i] = nums[i];           // first copy
            ans[i + n] = nums[i];       // second copy
        }
        return ans;
    }
};
