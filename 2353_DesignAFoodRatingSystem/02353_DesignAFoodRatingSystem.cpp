/*
MEDIUM: https://leetcode.com/problems/design-a-food-rating-system/


*/

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>

// NOTE: This is actually too slow. The faster solution keeps the ratings in sorted order, 
// That is, when changing the rating, we delete from m_foodToRatings and re-insert it.
// In my current solution, at worst case, this is linear: for(const auto& [food, rating] : m_foodToRatings[cuisine])
// But insertion and deletion from a set is log n
// Anyway, I definitely need to re-do this.
class FoodRatings {
public:

    FoodRatings(std::vector<std::string>& foods, std::vector<std::string>& cuisines, std::vector<int>& ratings) 
    {
        for(auto i = 0; i < foods.size(); ++i)
        {
            auto rating = std::make_shared<int>(ratings[i]);
            m_foodToRatings[cuisines[i]].try_emplace(foods[i], rating);
            m_foodToRatingsFlat.try_emplace(foods[i], rating);
        }
    }
    
    auto changeRating(const std::string& food, int newRating) -> void
    {
        *m_foodToRatingsFlat[food] = newRating;
    }
    
    auto highestRated(const std::string& cuisine) -> std::string
    {
        auto highestRatedFood = std::string{};
        auto highestRating = INT_MIN;
        for(const auto& [food, rating] : m_foodToRatings[cuisine])
        {
            if(*rating > highestRating)
            {
                highestRating = *rating;
                highestRatedFood = food;
            }
        }
        return highestRatedFood;
    }

private:
    
    // Cuisine to food to rating - ordered by cuisine and alphabetically.
    std::unordered_map<std::string, std::map<std::string, std::shared_ptr<int>>> m_foodToRatings;

    // Flat list of food rating - easy access for changing rating.
    std::unordered_map<std::string, std::shared_ptr<int>> m_foodToRatingsFlat;
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */

auto main(int argc, char * argv[]) -> int
{
    return 0;
}

