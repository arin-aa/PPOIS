#include "MetadataProvider.h"
#include <algorithm>
#include "MusicPlayerExceptions.h"

const std::string TITLE_KEY="title";
const std::string FORMAT_KEY="format";
const std::string SOURCE_KEY="source";

MetadataProvider::MetadataProvider(const std::string& apiUrl):apiUrl(apiUrl){}

std::map<std::string,std::string> MetadataProvider::fetchMetadata(const std::string& uri) const{
    if(apiUrl.empty()){
        throw MetadataException("metadata service is not available",OFFLINE_SOURCE);
    }
    std::string fileName=uri.substr(uri.find_last_of('/')+1);
    size_t dotPosition=fileName.find_last_of('.');
    if(dotPosition==std::string::npos){
        throw MetadataException("file has no extension: "+uri,apiUrl);
    }
    std::string title=fileName.substr(0,dotPosition);
    std::replace(title.begin(),title.end(),'_',' ');
    std::map<std::string,std::string> metadata;
    metadata[TITLE_KEY]=title;
    metadata[FORMAT_KEY]=fileName.substr(dotPosition+1);
    metadata[SOURCE_KEY]=apiUrl;
    return metadata;
}