/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Two Sum (LeetCode #001)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/two-sum/
 * NeetCode URL: https://neetcode.io/problems/two-integer-sum?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 15.8 MB)
 *
 * --- Intuition ---
 * While scanning the array we can ask: “What number do I need to pair with the current element to reach `target`?” If that needed value has already been seen, we have found the answer instantly.
 *
 * --- Approach ---
 * 1. Create an empty hash map `pos` that stores **value → index** for elements we have processed.
 * 2. Iterate over `nums` with index `i`.
 * * Compute the complement `need = target - nums[i]`.
 * * If `need` exists in `pos`, return `{pos[need], i}` – the two required indices.
 * * Otherwise insert the current pair `{nums[i], i}` into `pos` and continue.
 * 3. The problem guarantees a solution, so the loop will always return inside.
 *
 * --- Complexity ---
 * Time Complexity:  ** `O(n)` – each element is processed once and hash‑lookups are O(1) on average.
 * Space Complexity: ** `O(n)` – in the worst case we store all `n` elements in the map.
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
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // value -> index
        std::unordered_map<int, int> pos;
        pos.reserve(nums.size() * 2); // reduce rehashes

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            int need = target - nums[i];
            auto it = pos.find(need);
            if (it != pos.end()) {
                return {it->second, i};
            }
            // store current number for future complements
            pos[nums[i]] = i;
        }
        // According to the problem statement this line is never reached.
        return {};
    }
};
