/**
 * @file Comment.h
 * @brief Declaration of the Comment class.
 */
#pragma once
#include <string>

/**
 * @class Comment
 * @brief Text message that a user leaves under a track, a playlist or another comment.
 *
 * The target is written as "kind:id", for example "track:5" or "comment:3".
 */
class Comment{
private:
    int id;///<Unique identifier of the comment.
    std::string authorId;///<Identifier of the author.
    std::string targetId;///<Target of the comment in the form "kind:id".
    std::string text;///<Text of the comment.

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param authorId Identifier of the author.
 * @param targetId Target of the comment.
 * @param text Text of the comment.
 */
    Comment(int id,const std::string& authorId,const std::string& targetId,const std::string& text);

/**
 * @brief Checks whether the comment answers another comment.
 * @return true if the target is a comment.
 */
    bool isReply() const;
};