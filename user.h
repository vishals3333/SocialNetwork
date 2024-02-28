#ifndef USER_H
#define USER_H


#include "post.h"
#include <set>
#include <string>
#include <vector>

class User
{
public:
    // DEFAULT CONSTRUCTOR
    // pre: none
    // post: creates a new user
    User();

    // COPY CONSTRUCTOR
    // pre: none
    // post: creates a user with the given parameters
    User(int id, std::string  name, int  year, int zip, std::set<int> f);

    // CONSTANT MEMBERS
    // pre: none
    // post: returns the user id
    const int getId();

    // pre: none
    // post: returns the user name
    const std::string getName();

    // pre: none
    // post: returns the user birth year
    const int getYear();

    // pre: none
    // post: returns the user zip code
    const int getZip();

    // pre: none
    // post: returns the users's friends with reference
    std::set<int> & getFriends();

    // MUTANT MEMBERS
    // pre: none
    // post: adds a friends with the provided id
    void addFriend(const int & id);

    // pre: none
    // post: deletes friend with the provided id
    void deleteFriend(const int & id);

    // pre: none
    // post: checks if the provided user is a friend
    const bool isFriend(const int & id);

    // pre: none
    // post: add a post to user
    void addPost(Post*);

    // pre: none
    // post: get the posts
    std::vector<Post*> getPosts();

    // pre:none
    // post: print given number of posts
    std::string getPostsString(int howMany, bool showOnlyPublic);
private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
    std::vector<Post*> messages_ ;

    // INVARIANTS
    // id_ is the user's id
    // name_ is the users's name
    // year_ is the user's birth year
    // zip_ is the user's zip code
    // friends_ is a set that contains the id's of the user's friends
    // messages_ is a vector that has all the posts for this user
};

#endif // USER_H
