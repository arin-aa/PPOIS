#include "TagEditor.h"
#include <algorithm>
#include "MusicPlayerExceptions.h"

const std::string ARTIST_TAG="artist";
const std::string TITLE_TAG="title";
const std::string FORMAT_TAG="format";
const std::string ARTIST_SEPARATOR=" - ";

TagEditor::TagEditor():supportedFormats({"mp3","flac","wav","ogg"}){}

std::map<std::string,std::string> TagEditor::readTags(const std::string& uri){
    size_t dotPosition=uri.find_last_of('.');
    std::string format=dotPosition==std::string::npos?"":uri.substr(dotPosition+1);
    if(std::find(supportedFormats.begin(),supportedFormats.end(),format)==supportedFormats.end()){
        throw MetadataException("unsupported format: "+format,uri);
    }
    size_t nameStart=uri.find_last_of('/')+1;
    std::string name=uri.substr(nameStart,dotPosition-nameStart);
    std::map<std::string,std::string> tags;
    size_t separator=name.find(ARTIST_SEPARATOR);
    if(separator==std::string::npos){
        tags[TITLE_TAG]=name;
    }else{
        tags[ARTIST_TAG]=name.substr(0,separator);
        tags[TITLE_TAG]=name.substr(separator+ARTIST_SEPARATOR.size());
    }
    tags[FORMAT_TAG]=format;
    return tags;
}

std::string TagEditor::writeTags(const std::string& uri,const std::map<std::string,std::string>& tags){
    size_t dotPosition=uri.find_last_of('.');
    std::string format=dotPosition==std::string::npos?"":uri.substr(dotPosition+1);
    if(std::find(supportedFormats.begin(),supportedFormats.end(),format)==supportedFormats.end()){
        lastError="unsupported format: "+format;
        throw MetadataException(lastError,uri);
    }
    auto title=tags.find(TITLE_TAG);
    if(title==tags.end() || title->second.empty()){
        lastError="title is required";
        throw MetadataException(lastError,uri);
    }
    auto artist=tags.find(ARTIST_TAG);
    std::string folder=uri.substr(0,uri.find_last_of('/')+1);
    std::string artistPart=artist==tags.end()?"":artist->second+ARTIST_SEPARATOR;
    return folder+artistPart+title->second+"."+format;
}