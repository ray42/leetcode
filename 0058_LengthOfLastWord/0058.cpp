
#include <string>


class Solution 
{
public:
    auto lengthOfLastWord(const std::string& s) -> int
    {
        auto len = 0;
        // Go backwards
        for(auto i = static_cast<int>(s.size()-1); i >= 0; --i) 
        {
            if(s[i] != ' ')
            {
                ++len;
            }
            else if(len != 0) // For cases like "   fly me   to   the moon  ", we need to skip past thje spaces at the end
            {
                break;
            }
        }
        return len;
    }
};


auto main()-> int
{
    return 0;
}
