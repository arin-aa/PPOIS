#include "RadioStation.h"
#include "MusicPlayerExceptions.h"
#include "SearchQuery.h"

const std::string HTTP_PREFIX="http://";
const std::string HTTPS_PREFIX="https://";

RadioStation::RadioStation(const std::string& name,const std::string& streamUrl):name(name),streamUrl(streamUrl){}

std::string RadioStation::tuneIn() const{
    bool isHttp=streamUrl.rfind(HTTP_PREFIX,0)==0;
    bool isHttps=streamUrl.rfind(HTTPS_PREFIX,0)==0;
    if(!isHttp && !isHttps){
        throw PlaybackException("invalid stream address: "+streamUrl,START_POSITION_MS);
    }
    return streamUrl;
}

std::string RadioStation::classifyGenre(const std::vector<std::string>& genreNames) const{
    std::string normalizedName=SearchQuery(name).normalize();
    for(const std::string& genreName:genreNames){
        std::string normalizedGenre=SearchQuery(genreName).normalize();
        if(normalizedName.find(normalizedGenre)!=std::string::npos){
            return genreName;
        }
    }
    return "";
}