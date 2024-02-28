#include "network.h"
#include "iostream"
#include "fstream"
#include "set"
#include <queue>
#include "vector"
#include "stack"
#include "sstream"
#include "user.h"

Network::Network()
{
}

User* Network::getUser(int id)
{
    for(int i = 0; i < users_.size(); i++)
    {
        if(users_[i]->getId() == id)
        {
            return users_[i];
        }
    }
    return nullptr;
}

void Network::addUser(User* n)
{
    users_.push_back(n);
}

int Network::addConnection(std::string a, std::string b)
{   if(a == b)
    {
        return -1;
    }
    int f1 = 0;
    int f2 = 0;
    bool i1 = false;
    bool i2 = false;
    for(int i = 0; i < users_.size(); i++)
    {
        if(getUser(i)->getName()== a)
        {
            f1 = users_[i]->getId();
            i1 = true;
        }
        if(getUser(i)->getName()== b)
        {
            f2 = users_[i]->getId();
            i2 = true;
        }
    }
    if(i1 && i2)
    {
        if(!getUser(f1)->isFriend(f2))
        {
            getUser(f1)->addFriend(f2);
            getUser(f2)->addFriend(f1);
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int Network::deleteConnection(std::string a, std::string b)
{
    if(a == b)
    {
        return -1;
    }
    int f1 = 0;
    int f2 = 0;
    bool i1, i2;
    for(int i = 0; i < users_.size(); i++)
    {
        if(users_[i]->getName() == a)
        {
            f1 = users_[i]->getId();
            i1 = true;
        }
        if(users_[i]->getName() == b)
        {
            f2 = users_[i]->getId();
            i2 = true;
        }
    }
    if(i1 && i2 && getUser(f1)->isFriend(f2))
    {
        getUser(f1)->deleteFriend(f2);
        getUser(f2)->deleteFriend(f1);
        return 0;
    }
    else
    {
        return -1;
    }
}

const int Network::getId(std::string a)
{
    for(int i = 0; i < users_.size(); i++)
    {
        if(users_[i]->getName() == a)
        {
            return users_[i]->getId();
        }
    }
    return -1;
}

const int Network::numUsers()
{
    return users_.size();
}

const int Network::writeUsers(const char* fname)
{
    std::ofstream myFile;
    myFile.open(fname);
    if(myFile.fail())
    {
        return -1;
    }
    myFile << numUsers() << std::endl;

    for(int i = 0; i < users_.size(); i++)
    {
        myFile << users_[i]->getId() << std::endl;
        myFile << '\t' << users_[i]->getName() << std::endl;
        myFile << '\t' << users_[i]->getYear() << std::endl;
        myFile << '\t' << users_[i]->getZip() << std::endl;
        myFile << '\t';
        for(auto j = users_[i]->getFriends().begin(); j != users_[i]->getFriends().end(); j++)
        {
            myFile << *j << ' ';
        }
        myFile << std::endl;
    }
    myFile.close();
    return 0;
}

int Network::readUsers(char* fname) {
    std::ifstream file;
    file.open(fname);
    std::cout << fname << std::endl;
    if (!file.is_open()) {
        return -1; // file not open or not found
    }
    int n;
    file >> n;
    for (int i = 0; i < n; i ++) {
        int id;
        std::string first_name, last_name, name;
        int year;
        int zip;
        std::set<int> friends;
        friends.clear();

        file >> id;
        file >> first_name >> last_name;
        file >> year;
        file >> zip;
        name = first_name + " " + last_name;

        std::string line;
        std::getline(file, line); // read the \n at the end of the "zip" line
        std::getline(file, line);
        std::stringstream ss(line);

        int id2;
        while(ss >> id2) {
            friends.insert(id2);
        }
        User* u = new User(id, name, year, zip, friends);
        addUser(u);
    }
    return 0;
}

bool Network::inNetwork(const int id)
{
    for(int i = 0; i < numUsers(); i++)
    {
        if(i == id)
        {
            return true;
        }
    }
    return false;
}

const bool Network::isPath(const int from, const int to)
{
    std::queue<int> q;
    std::vector <bool> visited (numUsers(), 0);
    std::vector <int> prev (numUsers(), -1);

    visited[from] = true;
    q.push(from);
    while(q.size() > 0)
    {
        int cur = q.front();
        q.pop();
        for(auto neighbor: getUser(cur)->getFriends())
        {
            if(!visited[neighbor])
            {
                prev[neighbor] = cur;
                visited[neighbor] = true;
                q.push(neighbor);
            }
            if(neighbor == to)
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> Network::shortestPath(int from, int to)
{
    std::queue<int> q;
    std::vector <bool> visited (numUsers(), 0);
    std::vector <int> prev (numUsers(), -1);
    std::vector <int> output;
    if(inNetwork(from) == false || inNetwork(to) == false)
    {
        return output;
    }

    visited[from] = true;
    q.push(from);
    while(q.size() > 0)
    {
        int cur = q.front();
        q.pop();
        for(auto neighbor: getUser(cur)->getFriends())
        {
            if(!visited[neighbor])
            {
                prev[neighbor] = cur;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    if(!isPath(from, to))
    {
        return output;
    }
    int cur = to;
    while(cur != from)
    {
        output.push_back(cur);
        cur = prev[cur];
    }
    std::vector<int> res;
    res.push_back(from);
    for(int i = output.size() - 1; i >= 0; i--)
    {
        res.push_back(output[i]);
    }
    return res;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance)
{
    std::vector<int> output;
    if(!inNetwork(from))
    {   to = -1;
        return output;
    }
    for(int i = 0; i < numUsers(); i++)
    {
        if(shortestPath(from, users_[i]->getId()).size() == distance + 1)
        {
            to = users_[i]->getId();
            return shortestPath(from, to);
        }
    }
    return output;
}

const int Network::getScore(const int id1, const int id2)
{   int res = 0;
    for(auto j = getUser(id1)->getFriends().begin(); j != getUser(id1)->getFriends().end(); j++)
    {
        for(auto k = getUser(id2)->getFriends().begin(); k != getUser(id2)->getFriends().end(); k++)
        {
            if(*k == *j)
            {
                res += 1;
                break;
            }
        }
    }
    return res;
}

std::vector<int> Network::suggestFriends(int who, int& score)
{   int c_score = 0;
    score = 0;
    std::vector<int> res;
    if(!inNetwork(who))
    {
        return res;
    }
    for(int i = 0; i < numUsers(); i++)
    {   if(i != who)
        {
            if(shortestPath(who, i).size() > 0 && shortestPath(who, i).size() <= 3)
            {
                res.push_back(i);
            }
        }
    }
    for(int i = 0; i < res.size(); i++)
    {
        c_score = getScore(who, res[i]);
        score = std::max(c_score, score);
        c_score = 0;
    }
    return res;
}

std::vector<std::vector<int> > Network::groups()
{
    std::vector <bool> visited (numUsers(), 0);
    std::vector<std::vector<int> > res;
    for(int i = 0; i < numUsers(); i++)
    {   if(!visited[i])
        {
            std::stack<int> stck;
            std::vector<int> this_g;
            visited[i] = true;
            stck.push(i);
            this_g.push_back(i);
            while(stck.size() > 0)
            {
                int cur = stck.top();
                stck.pop();
                for(auto neighbor: getUser(cur)->getFriends())
                {
                    if(!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        stck.push(neighbor);
                        this_g.push_back(neighbor);
                    }
                }
            }
            res.push_back(this_g);
        }
    }
    return res;
}

void Network::addPost(int ownerId, std:: string message, int likes, bool isIncoming, std::string authorName, bool isPublic)
{
    if(inNetwork(ownerId))
    {  int messageId = 0;
        for(auto j: users_)
        {
            messageId += j->getPosts().size();
        }
       if(!isIncoming)
       {
            Post *p = new Post(messageId, ownerId, message, likes);
            getUser(ownerId)->addPost(p);
       }
       else
       {
            Post * p = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
            getUser(ownerId)->addPost(p);
       }
    }
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic)
{   return getUser(ownerId)->getPostsString(howMany, showOnlyPublic);
}

int Network::readPosts(char * fname)
{
    std::ifstream file;
    file.open(fname);
    std::cout << fname << std::endl;
    if (!file.is_open()) {
       return -1; // file not open or not found
    }
    int n;
    file >> n;
    file.ignore();
    for (int i = 0; i < n; i++)
    {
       int messageId, ownerId, likes;
       std::string line, message_txt, author, isPublic;
       bool isP;
       std::getline(file, line);
       messageId = std::stoi(line);
       std::getline(file, message_txt);
       file >> ownerId >> likes;
       file.ignore();
       std::getline(file, isPublic);
       std::getline(file, author);
       author.erase(std::remove(author.begin(), author.end(), '\t'), author.end());
       if(isPublic == "\tprivate")
       {
            isP = false;
       }
       else if(isPublic == "\tpublic")
       {
            isP = true;
       }

       if(author == "")
       {
            Post * p = new Post(messageId, ownerId, message_txt, likes);
            getUser(ownerId)->addPost(p);
       }
       else
       {
            Post * p = new IncomingPost(messageId, ownerId, message_txt, likes, isP, author);
            getUser(ownerId)->addPost(p);
       }
    }
    file.close();
    return 1;
}

bool Pcomp(Post * a, Post * b)
{
    return a->getMessageId() < b->getMessageId();
}

int Network::writePosts(char * fname)
{   std::ofstream myFile;
    myFile.open(fname);
    int ctr = 0;
    if(myFile.fail())
    {
       return -1;
    }
    std::vector <Post*> p;
    int n = 0;
    for(auto j: users_)
    {
       for(auto k:j->getPosts())
       {
            n += 1;
            p.push_back(k);
       }
    }

    sort(p.begin(), p.end(), Pcomp);
    myFile << n << std::endl;
    for(auto j: p)
    {
       myFile << j->getMessageId() << std::endl;
       myFile << "\t" << j->getMessage() << std::endl;
       myFile << "\t" << j->getOwnerId() << std::endl;
       myFile << "\t" << j->getLikes() << std::endl;
       if(j->getAuthor() == "")
       {
            myFile << '\n';
            myFile << '\n';
       }
       else
       {
            if(j->getIsPublic())
            {
                myFile << "\t" << "public" << std::endl;

            }
            else if(!j->getIsPublic())
            {
                myFile << "\t" << "private" << std::endl;
                //std::cout << "private" << std::endl;
            }
            myFile << '\t' << j->getAuthor() << std::endl;
       }
    }
    myFile.close();
    return 1;
}


