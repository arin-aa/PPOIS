#include "Comment.h"

const std::string COMMENT_TARGET_PREFIX="comment:";

Comment::Comment(int id,const std::string& authorId,const std::string& targetId,const std::string& text):
    id(id),authorId(authorId),targetId(targetId),text(text){}

bool Comment::isReply() const{
    return targetId.compare(0,COMMENT_TARGET_PREFIX.size(),COMMENT_TARGET_PREFIX)==0;
}