#include "TagEditor.h"
#include "MusicPlayerExceptions.h"

const std::string ARTIST_TAG="artist";
const std::string TITLE_TAG="title";
const std::string FORMAT_TAG="format";
const std::string ARTIST_SEPARATOR=" - ";
const char PATH_SEPARATOR='/';
const char EXTENSION_SEPARATOR='.';
const std::vector<std::string> SUPPORTED_FORMATS={"mp3","flac","wav","ogg"};

TagEditor::TagEditor():supportedFormats(SUPPORTED_FORMATS){}

std::string TagEditor::extractFormat(const std::string& uri) const{
    size_t dotPosition=uri.find_last_of(EXTENSION_SEPARATOR);
    std::string format=dotPosition==std::string::npos?"":uri.substr(dotPosition+1);
    for(const std::string& supportedFormat:supportedFormats){
        if(supportedFormat==format){
            return format;
        }
    }
    throw MetadataException("unsupported format: "+format,uri);
}

std::map<std::string,std::string> TagEditor::readTags(const std::string& uri){
    std::string format=extractFormat(uri);
    size_t nameStart=uri.find_last_of(PATH_SEPARATOR)+1;
    size_t nameLength=uri.size()-format.size()-1-nameStart;
    std::string name=uri.substr(nameStart,nameLength);
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
    std::string format=extractFormat(uri);
    auto title=tags.find(TITLE_TAG);
    if(title==tags.end() || title->second.empty()){
        throw MetadataException("title is required",uri);
    }
    auto artist=tags.find(ARTIST_TAG);
    size_t separatorPos=uri.find_last_of(PATH_SEPARATOR);
    std::string folder=uri.substr(0,separatorPos+1);
    std::string artistPart=artist==tags.end()?"":artist->second+ARTIST_SEPARATOR;
    return folder+artistPart+title->second+EXTENSION_SEPARATOR+format;
}