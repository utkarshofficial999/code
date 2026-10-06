/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Design HashSet (LeetCode #705)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/design-hashset/
 * NeetCode URL: https://neetcode.io/problems/design-hashset?list=neetcode250
 * Status: Accepted (Runtime: 15 ms, Memory: 49.7 MB)
 *
 * --- Intuition ---
 * Because the key range is bounded (`0 ≤ key ≤ 10⁶`) we can store the presence of each possible key directly in an array‑like structure. A simple boolean vector gives O(1) time for every operation and uses only about 1 MiB of memory, which easily satisfies the limits.
 *
 * --- Approach ---
 * 1. **Data structure** – Create a `std::vector<bool> present` of size `MAX_KEY + 1` (`MAX_KEY = 1'000'000`).
 * `present[x]` is `true` iff `x` has been added and not removed.
 * 2. **add(key)** – Set `present[key] = true`.
 * 3. **remove(key)** – Set `present[key] = false`. (If the key was never added the value stays `false`.)
 * 4. **contains(key)** – Return the value of `present[key]`.
 * 
 * All operations are direct array accesses, therefore constant time.
 *
 * --- Complexity ---
 * Time Complexity:  O(1) for add, remove, and contains.
 * Space Complexity: O(MAX_KEY) → O(10⁶) ≈ 1 MiB.
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

/*
 * Design a HashSet without using any built‑in hash table libraries.
 * The key range is 0 … 1,000,000, so a simple boolean vector is sufficient.
 */
class MyHashSet {
private:
    static constexpr int MAX_KEY = 1'000'000;          // inclusive upper bound
    std::vector<bool> present;                         // presence flag for each key

public:
    /** Initialize your data structure here. */
    MyHashSet() : present(MAX_KEY + 1, false) {}

    /** Inserts the value key into the HashSet. */
    void add(int key) {
        // Guard against out‑of‑range keys (defensive programming)
        if (key < 0 || key > MAX_KEY) return;
        present[key] = true;
    }

    /** Removes the value key from the HashSet. */
    void remove(int key) {
        if (key < 0 || key > MAX_KEY) return;
        present[key] = false;
    }

    /** Returns true if this set contains the specified element. */
    bool contains(int key) {
        if (key < 0 || key > MAX_KEY) return false;
        return present[key];
    }
};

/*
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
