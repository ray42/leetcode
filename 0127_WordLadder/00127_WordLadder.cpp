/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

    * Every adjacent pair of words differs by a single letter.
    * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    * sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

Constraints:

    1 <= beginWord.length <= 10
    endWord.length == beginWord.length
    1 <= wordList.length <= 5000
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.

#######################################################################

There are two things to realise in this problem
1) How to recognise that it's a graph problem
2) The "trick" to solve it so it passes leetcode's requirement checks.

1) When I first saw this problem, I thought "How do I get from hit to cog?"
and I was thinking, change one character, check if it's in the word list, etc...

but, since we are given the wordlist upfront, the words can be nodes.
There is a link between two nodes if the two words differ by at most one letter


2) How do we generate the adjacency list? 
If wordList = ["hit", "hot","dot","dog","lot","log","cog"]
Then we're used to something like:
[
hit: [hot]
hot: [hit, dot, lot]
...
]

What is the complexity of this? We need to go through each word, then for each word, we go through every word on the list to see if it differs by only one character.
Let N be the number of words and M be the length of a word. Then the complexity of generating the adjacency list is 
N*N*M
N - loop through all the words
N - loop through the words again to see if it differs by one character
M - the operation to check if it differs by one character.


Now, we know that there are these two constraints:

    1 <= beginWord.length <= 10
    1 <= wordList.length <= 5000


Thus, N^2 M would be large if N is large. We know that M is small, can we do something with that?

Neetcode had an alternate way of constructing the adjacency matrix. However, we don't even need one! What about this:


######################################

Actual Solution, from: https://leetcode.com/problems/word-ladder/solutions/6122964/bfs-solution-explanation-complexities-explained/

We still perform BFS. 

1) Put all the nodes in a hash set for easy lookup.

2) Have a queue to perform the BFS.

3)  We loop through the nodes by popping from the queue
        Now we construct all possible nodes by looping through the characters in the word
            for each character place, we loop through the alphabets

            if this new node is the end word, then we can return the number of steps (stored in the queue)

            otherwise, we can check if it's in the word list node set, if it is, then we push both the word and the number of steps to get to the node
            remove it from the word list set to prevent revisiting.

Note: The number of steps starts from 1.


Time: N for the set, N * L * 26 for the loop
Space: N*M for the set, N for the queue
*/

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

class Solution {
public:
    auto ladderLength(std::string& beginWord, std::string& endWord, std::vector<std::string>& wordList) -> int
    {
        auto setWordList = std::unordered_set<std::string>(wordList.begin(), wordList.end());

        if(!setWordList.contains(endWord)) return 0;

        auto queue = std::queue<std::pair<std::string,int>>{};

        queue.push({beginWord,1});

        while(!queue.empty())
        {
            // Get the word to loop through each character of the word and replace it with each letter of the alphabet
            auto [currentWord, step] = queue.front();
            queue.pop();

            for(auto i = 0; i < currentWord.size(); ++i)
            {
                auto currentLetter = currentWord[i];

                for(auto ch = 'a'; ch <= 'z'; ++ch)
                {
                    currentWord[i] = ch;

                    if(currentWord == endWord)
                    {
                        return step+1;
                    }
                    else if(setWordList.contains(currentWord))
                    {
                        queue.push({currentWord, step+1});
                        setWordList.erase(currentWord);
                    }
                }
                currentWord[i] = currentLetter;
            }
        }

        return 0;
    }
};






















auto main(int argc, char* argv[]) -> int
{
    return 0;
}
