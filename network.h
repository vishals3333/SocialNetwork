#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include "vector"


class Network
{
public:
    // default constructor
    // pre: none
    // post: creates an empty network
    Network();

    // CONSTANT MEMBERS
    // pre: none
    // post: returns id of userwith given name
    const int getId(std::string name);

    // pre:none
    // post: return numbers of users in network
    const int numUsers();

    // pre: none
    // post: returns vector containing shortest path starting at from ending at to
    std::vector<int> shortestPath(int from, int to);

    // MUTANT MEMBERS
    // pre: none
    // post: returns the user with given id
    User* getUser(int id);

    // pre: none
    // post: adds given user to network
    void addUser(User* n);

    // pre: none
    // post: adds connections between two provided users
    int addConnection(std::string s1, std::string s2);

    // pre: none
    // post: deletes connections between two provided users
    int deleteConnection(std::string s1, std::string s2);

    // pre: none
    // post: reads data from a given file onto network
    int readUsers(char* fname);

    // pre: none
    // post: writes data from network onto the provided file
    const int writeUsers(const char* fname);

    // pre: none
    // post: checks the distance between two users
    std::vector<int> distanceUser(int from, int& to, int distance);

    // pre: none
    // post: gives friends suggestions based on a sepcific score
    std::vector<int> suggestFriends(int who, int& score);

    // pre: none
    // post: get the score between two users
    const int getScore(const int id1, const int id2);

    // pre: none
    // post: return the connected componenets in the tree
    std::vector<std::vector<int> > groups();

    // pre: none
    // post: add a post with the given parameters
    void addPost(int ownerId, std:: string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    // pre: none
    // post: write out the messafe from a post
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    // pre: none
    // post: read posts from a file
    int readPosts(char* fname);

    // pre: none
    // post: write posts to a file
    int writePosts(char* fname);

    // Helper Functions:
    // check whether a user is in the network
    bool inNetwork(const int id);


private:
    std::vector<User*> users_;

    // INVARIANTS
    // users_ is a vector that contains a pointer to all the user's in the network


    // checks whether there is a path from one user to another
    const bool isPath(const int from, const int to);

};

#endif // NETWORK_H
