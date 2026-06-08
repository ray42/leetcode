/*



*/

#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

class TimeMap {
private: 
    
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> m = {};

public:
    TimeMap()
    {
        
    }
    
    void set(const std::string& key, const std::string& value, int timestamp)
    {
        m[key].emplace_back(value,timestamp);
    }
    
    std::string get(const std::string& key, int timestamp)
    {
        auto ret = std::string{};

        if(auto it = m.find(key); it != m.end())
        {
            // it points to a pair where first is the key, second is the value.
            const auto& v = it->second;

            // Now find the value where the time is closest to timestamp
            auto L = 0;
            auto R = static_cast<int>(v.size()-1);
            auto res = v[0];
            while(L <= R)
            {
                auto M = (L+R)/2;

                if(v[M].second <= timestamp)
                {
                    if(timestamp - v[M].second <= timestamp - res.second)
                    {
                        res = v[M];
                        ret = res.first;
                    }

                    // Look right for an even closer time to timestamp
                    L = M+1;
                }
                else
                {
                    // the time is greater than timestamp, so we need to look left
                    R = M-1;
                }

            }
        }
        return ret;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */


auto main(int argc, char* argv[]) -> int
{
    return 0;
}