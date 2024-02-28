#ifndef POST_H
#define POST_H

#include "string"


class Post
{
public:
    // DEFAULT CONSTRUCTOR
    // pre: none
    // post: creates empty post
    Post();

    // CONSTRUCTOR
    // pre: none
    // post: creates post with given parameters
    Post(int messageId, int ownerId, std::string message, int  likes);

    // pre: none
    // post: wrtie out the post in a specific format
    virtual std::string toString();

    // pre: none
    // post: get the message id
    int getMessageId();

    // pre: none
    // post: get the owner id
    int getOwnerId();

    // pre: none
    // post: get the message
    std::string getMessage();

    // pre: none
    // post: get number of likes
    int getLikes();

    // pre: none
    // post: get the author
    virtual std::string getAuthor();

    // pre: none
    // post: get the publicity
    virtual bool getIsPublic();
private:
    // CLASS INVARIANTS
    int messageId_ = 0;
    int ownerId_ = 0;
    std::string message_ = "";
    int likes_ = 0;


};

class IncomingPost:public Post
{
public:
    // pre: none
    // post: creates empty incoming post
    IncomingPost();

    // pre: none
    // post: parametrized incoming post
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    // pre: none
    // post: write message in a given format
    std::string toString();

    // pre: none
    // post: get the author
    std::string getAuthor();

    // pre: none
    // post: get the publicity
    bool getIsPublic();
private:
    // CLASS INVARIANTS
    std::string author_;
    bool isPublic_;

};

#endif // POST_H
