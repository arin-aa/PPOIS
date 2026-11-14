#include "MetadataProvider.h"
#include "MusicPlayerExceptions.h"

const std::string TITLE_KEY="title";
const std::string FORMAT_KEY="format";
const std::string SOURCE_KEY="source";
const char PATH_SEPARATOR='/';
const char EXTENSION_SEPARATOR='.';
const char FILE_WORD_SEPARATOR='_';
const char TITLE_WORD_SEPARATOR=' ';

MetadataProvider::MetadataProvider(const std::string& apiUrl):apiUrl(apiUrl){}

std::map<std::string,std::string> MetadataProvider::fetchMetadata(const std::string& uri) const{
    if(apiUrl.empty()){
        throw MetadataException("metadata service is not available",OFFLINE_SOURCE);
    }
    size_t separatorPos=uri.find_last_of(PATH_SEPARATOR);
    std::string fileName=uri.substr(separatorPos+1);
    size_t dotPosition=fileName.find_last_of(EXTENSION_SEPARATOR);
    if(dotPosition==std::string::npos){
        throw MetadataException("file has no extension: "+uri,apiUrl);
    }
    std::string title=fileName.substr(0,dotPosition);
    for(char& symbol:title){
        if(symbol==FILE_WORD_SEPARATOR){
            symbol=TITLE_WORD_SEPARATOR;
        }
    }
    return std::map<std::string,std::string>{{TITLE_KEY,title},{FORMAT_KEY,fileName.substr(dotPosition+1)},{SOURCE_KEY,apiUrl}};
}