
/*
// There are four ways to approach this problem:
// 1 Hashmap + sorting frequency
// 2 Hashmap + min heap
// 3 Hashmap + bucket sort
// 4 Hashmap + quickselect

## Variables

Let:

```text
n = total number of elements in nums
m = number of unique elements in nums
k = number of top frequent elements requested
```

Example:

```cpp
nums = [1,1,1,2,2,3]
k = 2
```

Then:

```text
n = 6
m = 3  // unique elements are 1, 2, 3
k = 2
```

***

## Complexity Comparison

| Approach                           |                        Time Complexity |                            Extra Space | Notes                                                                                                                                     |
| ---------------------------------- | -------------------------------------: | -------------------------------------: | ----------------------------------------------------------------------------------------------------------------------------------------- |
| **1. Hashmap + sorting frequency** |                       `O(n + m log m)` |                                 `O(m)` | Simple and clean. Count frequencies, then sort unique elements by frequency. Not optimal time because it fully sorts all unique elements. |
| **2. Hashmap + min heap**          |                       `O(n + m log k)` |                             `O(m + k)` | Good when `k` is small. Maintains a heap of only the best `k` candidates. More space-efficient than bucket sort in practice.              |
| **3. Hashmap + bucket sort**       |                                 `O(n)` | `O(n + m)` → usually written as `O(n)` | Best worst-case time complexity. Uses buckets indexed by frequency, but allocates a bucket array of size `n + 1`.                         |
| **4. Hashmap + quickselect**       | Average `O(n)`, worst-case `O(n + m²)` |                                 `O(m)` | Average linear time without the bucket array. More complex. Randomized pivot makes worst case unlikely.                                   |

***

## Slightly More Detailed Breakdown

### 1. Hashmap + Sorting Frequency

Steps:

```text
Count frequencies       -> O(n)
Store unique elements   -> O(m)
Sort by frequency       -> O(m log m)
Take first k elements   -> O(k)
```

Total:

```text
O(n + m log m)
```

Extra space:

```text
O(m)
```

You need the hashmap, and usually a vector of unique elements.

***

### 2. Hashmap + Min Heap

Steps:

```text
Count frequencies       -> O(n)
Push m unique elements  -> O(m log k)
Extract k elements      -> O(k log k), usually dominated
```

Total:

```text
O(n + m log k)
```

Extra space:

```text
O(m + k)
```

The hashmap stores `m` frequencies, and the heap stores at most `k` elements.

This is often the best practical choice when:

```text
k << m
```

For example:

```text
m = 100,000
k = 10
```

***

### 3. Hashmap + Bucket Sort

Steps:

```text
Count frequencies       -> O(n)
Create n + 1 buckets    -> O(n)
Place elements in buckets -> O(m)
Scan buckets backwards  -> O(n)
```

Total:

```text
O(n)
```

Extra space:

```text
O(n + m)
```

Usually simplified to:

```text
O(n)
```

This is the best asymptotic time solution, but as you pointed out earlier, it allocates:

```cpp
vector<vector<int>> buckets(nums.size() + 1);
```

So it may use more memory than the heap or quickselect approach.

***

### 4. Hashmap + Quickselect

Steps:

```text
Count frequencies       -> O(n)
Store unique elements   -> O(m)
Quickselect             -> average O(m), worst O(m²)
Take first k elements   -> O(k)
```

Total average:

```text
O(n + m)
```

Since `m <= n`, this is usually written as:

```text
Average O(n)
```

Worst case:

```text
O(n + m²)
```

Extra space:

```text
O(m)
```

This avoids both:

```text
full sorting
```

and:

```text
the n + 1 bucket array
```

So it is a strong option if you want average linear time with better practical memory usage than bucket sort.

***

## Summary

If asked in an interview:

```text
Sorting:       easiest to explain, O(n + m log m)
Min heap:      best when k is small, O(n + m log k)
Bucket sort:   best worst-case time, O(n), but uses O(n) bucket space
Quickselect:   average O(n), O(m) space, but more complex and worst-case O(m²)
```

For pure LeetCode optimal time, say:

```text
Hashmap + bucket sort
```

For a strong practical answer, mention:

```text
Quickselect gives average O(n) time with O(m) extra space.
```

And if `k` is very small:

```text
Hashmap + min heap is often preferable.
```

*/


#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <queue>

using namespace std;

class SolutionSorting {
public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;

    for (int num : nums) {
      freq[num]++;
    }

    vector<pair<int, int>> items;

    for (auto& [num, count] : freq) {
      items.push_back({ num, count });
    }

    sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
      return a.second > b.second;
      });

    vector<int> result;

    for (int i = 0; i < k; i++) {
      result.push_back(items[i].first);
    }

    return result;
  }
};

class SolutionMinHeap {
public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;

    for (int num : nums) {
      freq[num]++;
    }

    priority_queue<
      pair<int, int>,
      vector<pair<int, int>>,
      greater<pair<int, int>>
    > minHeap;

    for (auto& [num, count] : freq) {
      minHeap.push({ count, num });

      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }

    vector<int> result;

    while (!minHeap.empty()) {
      result.push_back(minHeap.top().second);
      minHeap.pop();
    }

    return result;
  }
};

class SolutionBucketSort {
public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;

    for (int num : nums) {
      freq[num]++;
    }

    vector<vector<int>> buckets(nums.size() + 1);

    for (auto& [num, count] : freq) {
      buckets[count].push_back(num);
    }

    vector<int> result;

    for (int i = nums.size(); i >= 0 && result.size() < k; i--) {
      for (int num : buckets[i]) {
        result.push_back(num);

        if (result.size() == k) {
          return result;
        }
      }
    }

    return result;
  }
};

class Solution {
private:
  // Random number generator used to choose a random pivot.
  // Random pivots help avoid consistently bad partition choices.
  mt19937 rng{ random_device{}() };

  /*
      Partition function rearranges items between indexes left and right.

      Goal:
      - Elements with frequency GREATER than pivot frequency go to the left.
      - Elements with frequency LESS THAN OR EQUAL to pivot frequency stay on the right.
      - Pivot ends up in its final sorted-by-frequency position.

      items contains pairs:
          {number, frequency}

      Example:
          items = [(1,3), (2,2), (3,4), (4,1)]
  */
  int partition(vector<pair<int, int>>& items, int left, int right, int pivotIndex) {
    // Get the frequency of the pivot element
    int pivotFreq = items[pivotIndex].second;

    // Move pivot to the end temporarily
    swap(items[pivotIndex], items[right]);

    // storeIndex marks where the next "higher frequency than pivot" element should go
    int storeIndex = left;

    // Loop through all elements except the pivot at items[right]
    for (int i = left; i < right; i++) {
      // We want higher frequencies on the left side
      if (items[i].second > pivotFreq) {
        swap(items[i], items[storeIndex]);
        storeIndex++;
      }
    }

    // Move pivot from the end to its final position
    swap(items[storeIndex], items[right]);

    // Return the final index of the pivot
    return storeIndex;
  }

  /*
      Quickselect partially sorts the vector.

      We do NOT need to fully sort all elements.
      We only need to ensure that the first k elements are the top k frequent ones.

      If k = 2, then target index = 1.
      We want indexes 0 and 1 to contain the two most frequent elements.
  */
  void quickselect(vector<pair<int, int>>& items, int k) {
    int left = 0;
    int right = items.size() - 1;

    // We want the pivot to land at index k - 1.
    // Then everything before it has frequency >= it.
    int target = k - 1;

    while (left <= right) {
      // Pick a random pivot index between left and right
      uniform_int_distribution<int> dist(left, right);
      int pivotIndex = dist(rng);

      // Partition around the pivot
      int finalPivotIndex = partition(items, left, right, pivotIndex);

      if (finalPivotIndex == target) {
        // The first k elements are now the top k frequent elements.
        return;
      }
      else if (finalPivotIndex < target) {
        // Pivot is too far left.
        // We still need more frequent elements on the right side.
        left = finalPivotIndex + 1;
      }
      else {
        // Pivot is too far right.
        // The top k elements are somewhere on the left side.
        right = finalPivotIndex - 1;
      }
    }
  }

public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    /*
        Step 1:
        Count how many times each number appears.

        Example:
            nums = [1,1,1,2,2,3]

        freq:
            1 -> 3
            2 -> 2
            3 -> 1
    */
    unordered_map<int, int> freq;

    for (int num : nums) {
      freq[num]++;
    }

    /*
        Step 2:
        Convert the hashmap into a vector of pairs.

        Each pair is:
            {number, frequency}

        Example:
            [(1,3), (2,2), (3,1)]
    */
    vector<pair<int, int>> items;

    for (auto& [num, count] : freq) {
      items.push_back({ num, count });
    }

    /*
        Step 3:
        Use quickselect so that the first k elements in items
        are the k most frequent elements.

        Their internal order does not matter.
    */
    quickselect(items, k);

    /*
        Step 4:
        Extract just the numbers from the first k pairs.
    */
    vector<int> result;

    for (int i = 0; i < k; i++) {
      result.push_back(items[i].first);
    }

    return result;
  }
};


