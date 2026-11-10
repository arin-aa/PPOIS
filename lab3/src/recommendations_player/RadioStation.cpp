#include "RadioStation.h"
#include <algorithm>
#include <cctype>
#include "MusicPlayerExceptions.h"

const std::string HTTP_PREFIX="http://";
const std::string HTTPS_PREFIX="https://";

static std::string toLower(std::string text){
    std::transform(text.begin(),text.end(),text.begin(),[](unsigned char symbol){
        return static_cast<char>(std::tolower(symbol));
    });
    return text;
}

RadioStation::RadioStation(const std::string& name,const std::string& streamUrl):name(name),streamUrl(streamUrl){}

static bool startsWith(const std::string& text,const std::string& prefix){
    return text.compare(0,prefix.size(),prefix)==0;
}

std::string RadioStation::tuneIn() const{
    bool isHttp=startsWith(streamUrl,HTTP_PREFIX);
    bool isHttps=startsWith(streamUrl,HTTPS_PREFIX);
    if(!isHttp && !isHttps){
        throw PlaybackException("invalid stream address: "+streamUrl,0);
    }
    return streamUrl;
}

std::string RadioStation::classifyGenre(const std::vector<std::string>& genreNames) const{
    std::string loweredName=toLower(name);
    for(const std::string& genreName:genreNames){
        std::string loweredGenre=toLower(genreName);
        size_t position=loweredName.find(loweredGenre);
        if(position!=std::string::npos){
            return genreName;
        }
    }
    return "";
}