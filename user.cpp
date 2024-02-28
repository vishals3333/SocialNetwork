#include "user.h"
#include <iterator>
#include "vector"
#include "set"

User::User()
{
}

User::User(int  id, std::string  name, int  year, int  zip, std::set<int> f)
{
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = f;
}

const int User::getId()
{
    return id_;
}

const int User::getYear()
{
    return year_;
}

const int User::getZip()
{
    return zip_;
}

std::set<int> & User::getFriends()
{
    return friends_;
}

const std::string User::getName()
{
    return name_;
}

void User::addFriend(const int & id)
{   bool already_friend = false;
    std::set<int>::iterator itr;
    for(itr = friends_.begin(); itr != friends_.end(); itr++)
    {
        if(*itr == id)
        {
            already_friend = true;
        }
    }
    if(!already_friend)
    {
        friends_.insert(id);
    }
}

void User::deleteFriend(const int & id)
{
    bool is_friend = false;
    bool already_friend = false;
    std::set<int>::iterator itr;
    for(itr = friends_.begin(); itr != friends_.end(); itr++)
    {
        if(*itr == id)
        {
            is_friend = true;
        }
    }
    if(is_friend)
    {
        friends_.erase(id);
    }
}

const bool User::isFriend(const int & id)
{
    for(auto j = friends_.begin(); j != friends_.end(); j++)
    {
        if(*j == id)
        {
            return true;
        }
    }

    return false;
}

void User::addPost(Post* p)
{
    messages_.push_back(p);
}

std::vector<Post*> User::getPosts()
{
    return messages_;
}

std::string User::getPostsString(int howMany, bool showOnlyPublic)
{   std::string res = "";
    int ctr = 0;
    for(auto p = messages_.rbegin(); p != messages_.rend(); p++)
    {
        auto &post = *p;
        if(((post->getIsPublic() && showOnlyPublic) || (!showOnlyPublic)) && (ctr < howMany))
        {
            res += post->toString();
            res += "\n";
            res += "\n";
            ctr += 1;
        }
    }
    return res;
}
