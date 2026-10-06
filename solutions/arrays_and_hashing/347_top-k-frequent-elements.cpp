/**
 * NeetCode 250 - Arrays & Hashing
 * Problem: Top K Frequent Elements (LeetCode #347)
 * Difficulty: Medium
 * LeetCode URL: https://leetcode.com/problems/top-k-frequent-elements/
 * NeetCode URL: https://neetcode.io/problems/top-k-elements-in-list?list=neetcode250
 * Status: Accepted (Runtime: 4 ms, Memory: 21.5 MB)
 *
 * --- Intuition ---
 * The frequency of each distinct number is at most `n`. By placing numbers into “buckets” indexed by their frequency we can retrieve the most frequent elements without any sorting, achieving linear time.
 *
 * --- Approach ---
 * 1. **Count frequencies** – traverse `nums` once and store `freq[x]` in an `unordered_map`.
 * 2. **Bucket by frequency** – create a vector of vectors `buckets` of size `n+1`; for each `(value, cnt)` push `value` into `buckets[cnt]`.
 * 3. **Collect answer** – iterate `buckets` from high frequency down to `1`, appending elements to the result until `k` elements have been taken.
 * 4. Return the result vector.
 *
 * --- Complexity ---
 * Time Complexity:  O(n) – one pass for counting, one pass for bucketing, and at most n elements scanned while collecting the answer.
 * Space Complexity: O(n) – hash map for frequencies and the bucket array (total size ≤ n + number_of_unique_elements).
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
#include <algorithm>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        // 1. Count frequencies
        std::unordered_map<int, int> freq;
        freq.reserve(nums.size() * 2);
        for (int x : nums) {
            ++freq[x];
        }

        // 2. Bucket by frequency (max frequency is nums.size())
        int n = nums.size();
        std::vector<std::vector<int>> buckets(n + 1);
        for (const auto& p : freq) {
            buckets[p.second].push_back(p.first);
        }

        // 3. Gather the top k frequent elements
        std::vector<int> ans;
        ans.reserve(k);
        for (int f = n; f >= 1 && ans.size() < static_cast<size_t>(k); --f) {
            for (int val : buckets[f]) {
                ans.push_back(val);
                if (ans.size() == static_cast<size_t>(k))
                    break;
            }
        }
        return ans;
    }
};
