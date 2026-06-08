
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Twitter {
public:

    // Key is user, the set is a list of users which the key user is following.
    std::unordered_map<int,std::unordered_set<int>> followings{};

    // First is the userId, Second is tweetId
    std::vector<std::pair<int,int>> tweets{};

    Twitter() {
        
    }
    
    void postTweet(int userId, int tweetId) {
        tweets.emplace_back(userId, tweetId);
    }
    
    std::vector<int> getNewsFeed(int userId) {
        // Start at the end of tweets, insert into res:
        // first == userId or followings[userId].contains(first)
        auto result = std::vector<int>{};
        for(auto i = std::ssize(tweets)-1; i >= 0 && std::ssize(result) < 10; --i)
        {
            if(tweets[i].first == userId || followings[userId].contains(tweets[i].first))
            {
                result.push_back(tweets[i].second);
            }
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        followings[followerId].emplace(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        followings[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

auto main(int argc, char* argv[]) -> int
{
//["Twitter","postTweet","getNewsFeed","follow","postTweet","getNewsFeed","unfollow","getNewsFeed"]
//[[],        [1,5],      [1],          [1,2],   [2,6],      [1],         [1,2],     [1]]

    auto sol = Twitter{};
    sol.postTweet(1,5);
    sol.getNewsFeed(1);
    sol.follow(1,2);
    sol.postTweet();
    sol.postTweet();
    sol.postTweet();
    sol.postTweet();

    return 0;
}
