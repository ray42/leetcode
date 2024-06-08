
#include <vector>
#include <string>
#include <unordered_set>


// With this solution, we generate all the possibilities in the sense that at each stage, we can choose to
// either add an ( or ) to the entry. However, there are restrictions, and they are:
// 1) The number of open parenthesis must be equal to or les than n
// 2) We can only insert a ) if the number of ( is currently greater than the number of ), since this means the ) has an opening brace to match.
class Solution {
public:
    auto generateParenthesis(const int n) -> std::vector<std::string>
    {
        
    }
};



// This solution builds up the combination of parenthesis like so:
// if n = 1, it will produce ()
// if n = 2, then we will first produce for n=1, then we insert a "()" where ever there is an open brace, finally we insert an entry where we have
//   () next to each other equal to the number of open braces we are suppose to have.
// E.g. say we want the entries for n = 2, and we have n = 1 = "()", then there is one open brace, given us:
//  (()), then we insert an entry where we have two () next to each other: "()()", thus, we have:
//  (()), ()()
// 
// for n = 3, then we get all the n = 2 entries and insert () where ever there is an (), then and generate the last entry of ():
//
// "(())" = (()()), ((()))
//          ^        ^
// "()()" = (())(), ()(())
//          ^         ^
// last entry: ()()()
// so we have:
// (()()), ((())), (())(), ()(()), )()()
//
// This looked like it works, but when we try to generate n = 4 using this method, we will get duplicate entries!
// this is why I have used an unordered_set to store them. ALSO, this means that this is less efficient since we are generating entries which
// we have already done.
// Now I'll try to understand neetcode's solution.
class SolutionInefficientDuplicatesGenerated {
public:
    auto generateParenthesis(const int n) -> std::vector<std::string>
    {
        auto ret = std::unordered_set<std::string>{};
        for(auto i = 1; i <= n; ++i)
        {
            auto ithParenCombination = std::unordered_set<std::string>{};

            // First we insert "()" where there is an open brace.
            for(const auto& v : ret)
            {
                // per token, there are i ways (the number of open braces)
                // So, per v, we generate up to i number of new combinations.
                for(auto j = 1; j <= i; ++j)
                {
                    auto vCopy = v;
                    const auto vCopySize = vCopy.size();
                    // Locate the jth open brace and insert "()", then push it into ithParenCombination
                    auto numOfOpenBrace = 0;
                    for(auto vi = 0; vi < vCopySize; ++vi)
                    {
                        if(vCopy[vi] == '(')
                        {
                            ++numOfOpenBrace;
                            if(numOfOpenBrace == j)
                            {
                                vCopy.insert(vi + 1,"()");
                                ithParenCombination.insert(vCopy);
                                break;
                            }
                        }
                    }
                }
            }

            // Finally, we insert ()()...(), i number of ().
            auto lastOne = std::string{};
            for(auto j = 1; j <= i; ++j)
            {
                lastOne += "()";
            }

            ithParenCombination.insert(lastOne);
            
            // Update ret
            ret = ithParenCombination;
        }

        return {ret.begin(), ret.end()};
    }
};


auto main(int argc, char * argv[]) -> int
{
    auto sol = Solution{};
    auto s0 = sol.generateParenthesis(0);
    auto iii0 = 42;
    auto s1 = sol.generateParenthesis(1);
    auto iii1 = 42;
    auto s2 = sol.generateParenthesis(2);
    auto iii2 = 42;
    auto s3 = sol.generateParenthesis(3);
    auto iii3 = 42;
    auto s4 = sol.generateParenthesis(4);
    auto iii4 = 42;

    auto iii = 42;
    return 0;
}

