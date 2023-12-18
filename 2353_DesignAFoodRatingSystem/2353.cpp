/*
MEDIUM: https://leetcode.com/problems/design-a-food-rating-system/

Design a food rating system that can do the following:

    Modify the rating of a food item listed in the system.
    Return the highest-rated food item for a type of cuisine in the system.

Implement the FoodRatings class:

    FoodRatings(String[] foods, String[] cuisines, int[] ratings) Initializes the system. The food items are described by foods, cuisines and ratings, all of which have a length of n.
        foods[i] is the name of the ith food,
        cuisines[i] is the type of cuisine of the ith food, and
        ratings[i] is the initial rating of the ith food.
    void changeRating(String food, int newRating) Changes the rating of the food item with the name food.
    String highestRated(String cuisine) Returns the name of the food item that has the highest rating for the given type of cuisine. If there is a tie, return the item with the lexicographically smaller name.

Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.

Example 1:

Input
["FoodRatings", "highestRated", "highestRated", "changeRating", "highestRated", "changeRating", "highestRated"]
[[["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]], ["korean"], ["japanese"], ["sushi", 16], ["japanese"], ["ramen", 16], ["japanese"]]
Output
[null, "kimchi", "ramen", null, "sushi", null, "ramen"]

Explanation
FoodRatings foodRatings = new FoodRatings(["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]);
foodRatings.highestRated("korean"); // return "kimchi"
                                    // "kimchi" is the highest rated korean food with a rating of 9.
foodRatings.highestRated("japanese"); // return "ramen"
                                      // "ramen" is the highest rated japanese food with a rating of 14.
foodRatings.changeRating("sushi", 16); // "sushi" now has a rating of 16.
foodRatings.highestRated("japanese"); // return "sushi"
                                      // "sushi" is the highest rated japanese food with a rating of 16.
foodRatings.changeRating("ramen", 16); // "ramen" now has a rating of 16.
foodRatings.highestRated("japanese"); // return "ramen"
                                      // Both "sushi" and "ramen" have a rating of 16.
                                      // However, "ramen" is lexicographically smaller than "sushi".

Constraints:

    1 <= n <= 2 * 104
    n == foods.length == cuisines.length == ratings.length
    1 <= foods[i].length, cuisines[i].length <= 10
    foods[i], cuisines[i] consist of lowercase English letters.
    1 <= ratings[i] <= 108
    All the strings in foods are distinct.
    food will be the name of a food item in the system across all calls to changeRating.
    cuisine will be a type of cuisine of at least one food item in the system across all calls to highestRated.
    At most 2 * 104 calls in total will be made to changeRating and highestRated.
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

