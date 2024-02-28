#include "post.h"
Post::Post()
{
}
Post::Post(int messageId, int ownerId, std::string message, int  likes)
{
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}

std::string Post::toString()
{
    return message_ + " Liked by "  + std::to_string(likes_) + " people.";
}

std::string Post::getMessage()
{
    return message_;
}

int Post::getMessageId()
{
    return messageId_;
}

int Post::getOwnerId()
{
    return ownerId_;
}

int Post::getLikes()
{
    return likes_;
}

bool Post::getIsPublic()
{
    return true;
}

std::string Post::getAuthor()
{
    return "";
}


IncomingPost::IncomingPost()
{
}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author)
    :Post(messageId, ownerId,  message, likes)
{
    isPublic_ = isPublic;
    author_ = author;
}


std::string IncomingPost::getAuthor()
{
    return author_;
}

bool IncomingPost::getIsPublic()
{
    return isPublic_;
}

std::string IncomingPost::toString()
{   std::string priv;
    if(isPublic_)
    {
         return author_ + " wrote: " + Post::toString();
    }
    else if(!isPublic_)
    {
        return author_ + " wrote:" + "(private)"+ Post::toString();
    }
}
