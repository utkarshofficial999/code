/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Design HashMap (LeetCode #706)
 * Difficulty: Easy
 * LeetCode URL: https://leetcode.com/problems/design-hashmap/
 * NeetCode URL: https://neetcode.io/problems/design-hashmap?list=neetcode250
 * Status: Accepted (Runtime: 52 ms, Memory: 229.2 MB)
 *
 * --- Intuition ---
 * Because the keys are bounded (`0 ≤ key ≤ 10⁶`) we can allocate a flat array indexed directly by the key. Using a special sentinel (‑1) tells us whether a slot is empty, giving true‑O(1) time for all operations without any hashing or chaining.
 *
 * --- Approach ---
 * 1. Allocate a `std::vector<int>` of size `MAX_KEY + 1` (`MAX_KEY = 1'000'000`).
 * 2. Initialise every entry with `-1` – the sentinel meaning “no mapping”.
 * 3. **put(key, value)** – store `value` at `table[key]`.
 * 4. **get(key)** – return `table[key]` (or `-1` if it still holds the sentinel).
 * 5. **remove(key)** – reset `table[key]` back to `-1`.
 * 
 * All operations are direct array accesses, therefore constant time.
 *
 * --- Complexity ---
 * Time Complexity:  O(1) for put, get, and remove.
 * Space Complexity: O(MAX_KEY) → O(10⁶) integers ≈ 4 MB.
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
#include <cstddef>   // for nullptr

class MyHashMap {
public:
    /** Initialize your data structure here. */
    MyHashMap() : table(MAX_KEY + 1, SENTINEL) {}

    /** Insert a (key, value) pair into the HashMap.
        If the key already exists, update the corresponding value. */
    void put(int key, int value) {
        table[key] = value;
    }

    /** Returns the value to which the specified key is mapped,
        or -1 if this map contains no mapping for the key. */
    int get(int key) const {
        return table[key];
    }

    /** Removes the mapping of the specified value key
        if this map contains a mapping for the key. */
    void remove(int key) {
        table[key] = SENTINEL;
    }

private:
    static constexpr int MAX_KEY = 1'000'000;   // given constraint
    static constexpr int SENTINEL = -1;        // value never used as a legitimate stored value
    std::vector<int> table;                    // direct‑address table
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
