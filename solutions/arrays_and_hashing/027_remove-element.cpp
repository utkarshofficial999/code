/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Remove Element (LeetCode #027)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/remove-element/
 * NeetCode URL: https://neetcode.io/problems/remove-element?list=neetcode250
 * Status: Accepted (Runtime: 0 ms, Memory: 11.6 MB)
 *
 * --- Intuition ---
 * We only need to keep the elements that are **not** equal to `val`.
 * By scanning the array from the front and, whenever we meet a `val`, swapping it with an element from the back that we have not examined yet, we can discard the unwanted value in O(1) extra space. The scan stops when the two pointers meet, and the left pointer’s index equals the number of kept elements.
 *
 * --- Approach ---
 * 1. Let `left = 0` (the next position to store a good element) and `right = nums.size() - 1` (the last unchecked element).
 * 2. While `left <= right`
 * * If `nums[left] == val` → swap `nums[left]` with `nums[right]` and decrement `right`. The element swapped in from the back has not been examined yet, so we keep `left` unchanged to re‑evaluate it.
 * * Otherwise (`nums[left] != val`) → the element is already in the correct place, just increment `left`.
 * 3. When the loop ends, all indices `[0, left)` contain values different from `val`. Return `left` as the new length `k`.
 *
 * --- Complexity ---
 * Time Complexity:  ** `O(n)` – each element is examined at most once.
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
#include <algorithm>   // for std::swap

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        // Two‑pointer technique: left scans forward, right scans backward.
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            if (nums[left] == val) {
                // Discard nums[left] by swapping with an unchecked element at 'right'.
                std::swap(nums[left], nums[right]);
                --right;               // shrink the considered range
                // Do NOT increment left: the element swapped in must be checked.
            } else {
                ++left;                // good element, move to next position
            }
        }
        // 'left' is the count of elements not equal to val.
        return left;
    }
};
