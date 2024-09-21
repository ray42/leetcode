/*
We do four methods:

1) Brute force by sorting
2) Heap
3) Quick Select
4) Median of medians
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <ranges>

// Time Complexity: O(nlog n) for the sort
// Space: O(1) since we are not using any extra storage
class SolutionBruteForce {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        std::ranges::sort(nums);

        // If k = 1, we need to get the biggest element (last element), which is nums.size() - 1.
        // If we need to get the kth biggest element which is nums.size() - k.
        return nums[nums.size() - k];
    }
};

// Since we want to find the kth LARGEST element, we will use a max heap to keep the max element at the top of the heap.
// If k = 1, we pop 0 times then return the top.
// If k = 2, we pop 1 times and return the top.
// In other words, we pop once less than k, so we can pop while(k > 1){... --k}
//
// Time Complexity: 
// Heapify: O(N)
// Pop k times = K Log N
// Best case is O(N) when k = 1 so we just pop once
// Worst case is N Log N when k = N.
// 
// Note: we can do an implementation where we use a min heap OR max heap depending on how far down k is.
// If K > N/2, then we can use a min heap and get the (N-K+1)th smallest element:
//
// 5
// 4
// 3
// 2 - 4th largest element
// 1
//
// This is the same as getting the 5-4+1 = 2nd smallest element.
//
// Space Complexity: N for the heap.
class SolutionHeap {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        auto pq = std::priority_queue<int, std::vector<int>, std::less<int>>{nums.begin(), nums.end()};

        while(k > 1)
        {
            pq.pop();
            --k;
        }

        return pq.top();
    }
};


class SolutionQuickSelect {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        return quickSelect(nums, 0, nums.size()-1,k);
    }

    auto quickSelect(std::vector<int>& v, int l, int r, int k)-> int
    {
        // partition the array and return the index of the pivot
        auto partition = [](std::vector<int>& v, int l, int r){
            
            // Use the last element as the pivot
            auto p = v[r];

            // Next potential position of the left partition
            auto i = l;

            // Loop from left to one less than r, at each j, we check if we should move it to the 
            // next potential left partition index i
            for(auto j = l; j < r; ++j)
            {
                if(v[j] <= p)
                {
                    std::swap(v[j], v[i]);

                    // Increment because this will be the next potential left partition position.
                    ++i;
                }
            }

            // i is now where the pivot element should be, v[r] is the pivot element
            std::swap(v[i], v[r]);

            return i;
        };

        auto pivotIndex = partition(v, l, r);
        if(pivotIndex == k - 1)
        {
            return v[pivotIndex];
        }
        else if(k-1 < pivotIndex) // The required element (k-1) is to the left of the pivot.
        {
            return quickSelect(v,l,pivotIndex-1,k);
        }
        else
        {
            return quickSelect(v,pivotIndex-1,r,k);
        }
    }
};


auto main(int argc, char* argv[]) -> int
{
    auto v = std::vector<int>{3,2,1,5,6,4};
    auto iii = SolutionQuickSelect{}.findKthLargest(v, 2);
    auto i = 42;
    return 0;
}
