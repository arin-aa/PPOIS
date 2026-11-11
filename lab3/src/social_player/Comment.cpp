#include "Comment.h"

const std::string COMMENT_TARGET_PREFIX="comment:";

Comment::Comment(int id,const std::string& authorId,const std::string& targetId,const std::string& text):
    id(id),authorId(authorId),targetId(targetId),text(text){}

bool Comment::isReply() const{
    return targetId.rfind(COMMENT_TARGET_PREFIX,0)==0;
}