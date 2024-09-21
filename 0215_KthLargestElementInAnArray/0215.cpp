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
#include <iostream>

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
        // Partitions the portion of num indicated by the index L and R inclusively
        // The element nums[R] will be chosen as the pivot
        auto partition = [&nums](int Li, int Ri)-> int
        {
            auto p = nums[Ri];// pivot

            // Next potential place for the LHS partition
            auto Ii = Li;

            // Loop through [L,R), and keep putting elements into position I and updating I.
            for(auto Ji = Li; Ji < Ri; ++Ji)
            {
                if(nums[Ji] <p)
                {
                    // Put elements at position J into the next potential LHS position
                    std::swap(nums[Ji], nums[Ii]);
                    ++Ii;
                }

            }
            
            // Put the pivot element in the correct place.
            std::swap(nums[Ii], nums[Ri]);

            return Ii;
        };

        auto quickSelect = [&nums, &partition](int Li, int Ri, int Ki, auto &&quickSelect) -> int
        {
            auto Pi = partition(Li,Ri);

            // If K = 1, it means we want the largest, i.e. when Pi = nums.size() - 1
            // If K = 2, it means we want the second largest, i.e. when Pi = nums.size() - 2
            // In other words, we can end when we get Pi = nums.size()-Ki
            if(Pi == nums.size() - Ki)
            {
                return nums[Pi];
            }
            else if(nums.size() - Ki < Pi) // We look to the left of the pivot
            {
                return quickSelect(Li, Pi-1, Ki, quickSelect);
            }
            else
            {
                return quickSelect(Pi+1, Ri, Ki, quickSelect);
            }
            return 0;
        };

        return quickSelect(0, nums.size()-1,k, quickSelect);
    }
};

auto main(int argc, char* argv[]) -> int
{
    //auto v = std::vector<int>{3,2,1,5,6,4};
    //auto iii = SolutionQuickSelect{}.findKthLargest(v, 2);
    //auto i = 42;
    auto factorial2 = [](int n, auto && factorial2) {
        if (n == 1 || n==0) return n;
        return n * factorial2(n - 1, factorial2);
        };
    std::cout << factorial2(5,factorial2) << std::endl;;
    return 0;
}
