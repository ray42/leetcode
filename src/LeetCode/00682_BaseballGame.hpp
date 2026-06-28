#pragma once
/*
Easy https://leetcode.com/problems/baseball-game/
*/

#include <vector>
#include <stack>
#include <string>
#include <functional> // for std::plus
#include <numeric>
#include <algorithm>
#include <cctype>

class Solution682 {
public:
  auto calPoints(const std::vector<std::string>& operations) const -> int
  {
    auto record = std::stack<int>{};
    for (const auto& op : operations)
    {
      switch (op[0])
      {
      case '+':
      {
        auto lastNumber = record.top();
        record.pop();
        auto secondLastNumber = record.top();
        record.push(lastNumber);
        record.push(lastNumber + secondLastNumber);
      }
      break;
      case 'D':
      {
        record.push(2 * record.top());
      }
      break;
      case 'C':
      {
        record.pop();
      }
      break;
      default:
      {
        record.push(std::stoi(op));
      }
      }
    }
    auto ret = 0;
    while (!record.empty())
    {
      ret += record.top();
      record.pop();
    }
    
    return ret;
    
    // Done using vector, which is better for this problem.
    // since we need to access the last two elements, and vector is better for that.
    //  auto resVec = std::vector<int>{};
    //  for(const auto& op : operations)
    //  {
    //    //const auto& c = op[0];
    //      if(op[0] == '+')
    //      {
    //          const auto lastPos = resVec.size()-1;
    //          resVec.push_back(resVec[lastPos] + resVec[lastPos-1]);
    //      }
    //      else if(op[0] == 'D')
    //      {
    //          const auto lastPos = resVec.size()-1;
    //          resVec.push_back(2*resVec[lastPos]);
    //      }
    //      else if(op[0] == 'C')
    //      {
    //          resVec.pop_back();
    //      }
    //      else
    //      {
    //          resVec.push_back(std::stoi(op));
    //      }
    //  }
    //
    //  return std::accumulate(resVec.begin(), resVec.end(),0, std::plus<int>{});
  }
};

/*
auto main(int argc, char* argv[]) -> int
{
  return 0;
}
*/
