#include "Artwork.h"

const std::string THUMBNAIL_SUFFIX="_thumb";
const char EXTENSION_SEPARATOR='.';

Artwork::Artwork(const std::string& uri):uri(uri){}

std::string Artwork::getThumbnailUri() const{
    size_t dotPosition=uri.find_last_of(EXTENSION_SEPARATOR);
    if(dotPosition==std::string::npos){
        return uri+THUMBNAIL_SUFFIX;
    }
    return uri.substr(0,dotPosition)+THUMBNAIL_SUFFIX+uri.substr(dotPosition);
}