/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Majority Element (LeetCode #169)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/majority-element/
 * NeetCode URL: https://neetcode.io/problems/majority-element?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 42.2 MB)
 *
 * --- Intuition ---
 * The majority element appears more than half of the array length, so if we pair each occurrence of a non‑majority element with a different element, the majority element will always remain unpaired. Maintaining a candidate and a counter while scanning the array captures this cancellation process.
 *
 * --- Approach ---
 * 1. Initialise `candidate` with any value (e.g., `nums[0]`) and `count = 0`.
 * 2. Iterate through the array:
 * * If `count` is `0`, set `candidate = nums[i]` and `count = 1`.
 * * Otherwise, increment `count` if `nums[i] == candidate`; else decrement `count`.
 * 3. After the single pass, `candidate` is guaranteed to be the majority element (the problem guarantees its existence).
 * 4. Return `candidate`.
 *
 * --- Complexity ---
 * Time Complexity:  ** `O(n)` – one linear scan of the array.
 * Space Complexity: ** `O(1)` – only a few integer variables are used.
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
    int majorityElement(std::vector<int>& nums) {
        // Boyer–Moore Voting Algorithm
        int candidate = 0;   // placeholder, will be set when count becomes 0
        int count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
                count = 1;
            } else if (num == candidate) {
                ++count;
            } else {
                --count;
            }
        }

        // The problem guarantees that a majority element exists,
        // so no further verification is required.
        return candidate;
    }
};
