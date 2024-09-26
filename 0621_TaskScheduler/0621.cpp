
/*
You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n. 
Each CPU interval can be idle or allow the completion of one task. 
Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.

Return the minimum number of CPU intervals required to complete all tasks.


Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2

Output: 8

Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.

After completing task A, you must wait two intervals before doing A again. The same applies to task B. 
In the 3rd interval, neither A nor B can be done, so you idle. By the 4th interval, you can do A again as 2 intervals have passed.

------------------------------------------------------------------------------------------------

Intuition and solution

Intuition 1: So the n means how many cycles are needed before we can repeat a task.
E.g. if n = 2, and the task is A, then:

A, X, X, A
|-----|

So n = 2 means that A + 2 more will form a "cycle". So the length of the cycle is n+1 tasks.

That is, let's say we begin by choosing "A", then we need to choose n more different letters before we choose A again.
So, this forms a n+1 cycle.

------------------------------------------------

Intuition 2: In a cycle, we should choose the highest frequency letters first.
Because this will give it more time before we can use that same letter again.

------------------------------------------------

Intuition 3: In a cycle, because we are selecting the highest frequency tasks first, 
             what comes afterwards (in the same cycle), must be equal to (in terms of frequency), or less than
             the ones before it. 
             This is important because, when we come to pick tasks for the next cycle, we can be sure that,
             as long as we pick the highest frequency one, we don't end up violating the constraint.


             E.g., Say we have A:10, B:5, n = 1, then we can do this:
             One Cycle: A, B
                        |--|
            
            when we continue the cycle, we long as we pick the highest frequency one first (A), we won't violate the constraint:
            A, B, A - constraint not violated
            A, B, B - constraint VIOLATED

            What can we conclude from this? This means that we don't even care about the letters, because, let's say we have:
            A: 10, B: 10, (10 of each)then if we form:

            A,B

            We know that we have 9 As and 9 Bs left - when we start the new cycle, do we actually care which pile we take from?
            We do and we don't. We do because if the last cycle is A,B, then we know that we want to pick A, B again.
            But we don't really, because if we picked B,A for the second cycle, this implies that our previous cycle could have been B,A,
            so we have B,A,B,A,...

            That is, if the frequencies of any two tasks are the same, they are interchangeable. This means that, only the frequencies are important.

------------------------------------------------

Given the above intuitions, we propose the following algorithm:

We know we need to pick the most frequent tasks first and that what tasks the frequencies belong to does not matter.
So we calculate the frequencies and put them in a max heap

For n+1 or when the heap is empty,
    
    pop the frequencies

    minus 1 from the freqs and store them in a TEMP container to re-populate the heap.


Push the updated frequencies back into the heap.

Update the time - if the heap if EMPTY, it means it means we have used up all the available tasks, so we just add in the number of tasks we just processed in the cycle.
                  if the heap is NOT empty, it means that two things:
                      1) We have filled the cycle with enough tasks and there are still some left over.
                      E.g. let the tasks be A:10, B:10, C:10, D:10, E:10 (there are 10 of each) and n=2, this means a cycle has n+1=3 items,
                      So when we have completed a cycle, we have:
                      A, B, C

                      the heap has: {10, 10} (for D and E)
                      the TEMP container: {9,9,9}

                      so we put the 9,9,9 back in:
                      heap: {10,10,9,9,9}

                      How much time have we used? It'll be the number of tasks processed, which in this case is equal to n+1=3 (For A,B,C)

                      2) We have not filled up the cycle, but there are no tasks left. E.g.
                      tasks: A:10,B:10, n = 2, so a cycle has n+1 = 3 items.

                      Heap: {10,10}

                      We process 2 tasks, the heap and temp vector are now:
                      Heap: {}
                      Temp: {9,9}

                      But we know that a cycle has 3 tasks. Putting Temp back into Heap, we have:
                      Heap: {9,9}

                      but how much should our time be incremented by? It would be n+1, since we need to have an "idle" task to reach n=3.


                THIS IS WHY TIME += HEAP.EMPTY() ? NUM_TASKS_PROCESSED : N+1
                                                   ^ PART 1              ^ PART 2

            We keep going until there are no items left in the heap.

            Let's code this up.
*/

#include <vector>
#include <queue>
#include <ranges>

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n)
    {
        // Count the frequencies and build the heap
        int freq[26]{0};

        for(const auto c : tasks)
        {
            ++freq[c-'A'];
        }

        auto pq = std::priority_queue<int, std::vector<int>, std::less<int>>{};
        for(const auto& f : freq)
        {
            if(f > 0) pq.push(f);
        }

        auto time = int{};

        while(!pq.empty())
        {
            auto store = std::vector<int>{};
            auto numberOfTasksProcessed = 0;
            auto tasksLeftInCycle = n + 1;
            while(tasksLeftInCycle > 0 && !pq.empty())
            {
                // If it's less than 1, there is no need to store it because there are no instances of this task after processing.
                if(auto nextFreq = pq.top() - 1; nextFreq > 0)
                {
                    store.push_back(nextFreq);
                }

                pq.pop();
                numberOfTasksProcessed++;
                tasksLeftInCycle--;
            }

            // Push the store for the next round.
            for(auto f : store)
                pq.push(store);

            // Update the time, using the long ass logic I wrote above.
            time += pq.empty() ? numberOfTasksProcessed : n+1;
        }

        return time;
    }
};


auto main(int argc, char* argv[]) -> int
{
    return 0;
}
