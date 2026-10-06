/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Sort an Array (LeetCode #912)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/sort-an-array/
 * NeetCode URL: https://neetcode.io/problems/sort-an-array?list=neetcode250
 * Status: Accepted (Runtime: 1481 ms, Memory: 70.9 MB)
 *
 * --- Intuition ---
 * The only requirement is to reorder the elements into non‑decreasing order without calling any library sorting routine.  An in‑place quick‑sort with a random pivot gives the desired average **O(n log n)** running time while using only **O(log n)** auxiliary stack space (the recursion depth).
 *
 * --- Approach ---
 * 1. **Randomised partition** – pick a pivot uniformly at random, swap it to the end and partition the range `[l, r]` so that all elements `< pivot` are on the left and the rest on the right.
 * 2. **Recursive quick‑sort** – recursively sort the left part `[l, p‑1]` and the right part `[p+1, r]`.
 * 3. **Tail‑call optimisation** – always recurse on the smaller sub‑range first and iterate on the larger one. This guarantees that the recursion depth never exceeds `O(log n)`.
 * 4. The algorithm works for any integer values, including negatives, and needs no extra containers.
 *
 * --- Complexity ---
 * Time Complexity:  Average O(n log n) (randomised pivot prevents the pathological O(n²) case).
 * Space Complexity: O(log n) auxiliary stack space due to recursion depth; the array itself is sorted in‑place.
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
    // public entry point
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
        return nums;
    }

private:
    // random number generator for pivot selection
    static int randomPivot(int l, int r) {
        static std::mt19937 rng(
            (unsigned)chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(l, r);
        return dist(rng);
    }

    // partition using Lomuto scheme
    static int partition(vector<int>& a, int l, int r) {
        int pivotIdx = randomPivot(l, r);
        swap(a[pivotIdx], a[r]);               // move pivot to end
        int pivot = a[r];
        int i = l;                              // place for next smaller element
        for (int j = l; j < r; ++j) {
            if (a[j] < pivot) {
                swap(a[i], a[j]);
                ++i;
            }
        }
        swap(a[i], a[r]);                       // put pivot into its final place
        return i;
    }

    // in‑place quick‑sort with tail‑recursion elimination
    static void quickSort(vector<int>& a, int l, int r) {
        while (l < r) {
            int p = partition(a, l, r);
            // Recurse on the smaller side first to keep stack depth O(log n)
            if (p - l < r - p) {
                quickSort(a, l, p - 1);
                l = p + 1;          // iterate on the larger right part
            } else {
                quickSort(a, p + 1, r);
                r = p - 1;          // iterate on the larger left part
            }
        }
    }
};
