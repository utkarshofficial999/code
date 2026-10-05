/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Contains Duplicate (LeetCode #217)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/contains-duplicate/
 * NeetCode URL: https://neetcode.io/problems/duplicate-integer?list=neetcode250
 * Status: Accepted (Runtime: 79 ms, Memory: 107.7 MB)
 *
 * --- Intuition ---
 * If any number appears twice, we will encounter it again while scanning the array. Keeping a hash set of the values we have already seen lets us detect a repeat in O(1) average time per element.
 *
 * --- Approach ---
 * 1. Create an `unordered_set<int>` to store numbers that have been visited.
 * 2. Iterate through `nums`.
 * * If the current number is already in the set, a duplicate exists → return `true`.
 * * Otherwise insert the number into the set and continue.
 * 3. If the loop finishes without finding a repeat, return `false`.
 * 4. To improve performance on large inputs, reserve space in the set (`set.reserve(nums.size())`) to avoid many re‑hashes.
 *
 * --- Complexity ---
 * Time Complexity:  ** O(n) – each element is processed once, and set operations are O(1) on average.
 * Space Complexity: ** O(n) – in the worst case all elements are distinct and are stored in the set.
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
#include <unordered_set>

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        // Reserve enough buckets to avoid frequent rehashing.
        std::unordered_set<int> seen;
        seen.reserve(nums.size());

        for (const int& x : nums) {
            // If x is already present, we have a duplicate.
            if (seen.find(x) != seen.end()) {
                return true;
            }
            seen.insert(x);
        }
        // No duplicates found.
        return false;
    }
};
