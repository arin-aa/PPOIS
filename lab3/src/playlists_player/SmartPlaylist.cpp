#include "SmartPlaylist.h"
#include <stdexcept>
#include "MediaLibrary.h"
#include "Track.h"

const char RULE_SEPARATOR=':';
const std::string GENRE_KEY="genre";
const std::string ARTIST_KEY="artist";
const std::string MIN_DURATION_KEY="minDuration";
const std::string MAX_DURATION_KEY="maxDuration";
const std::string TITLE_KEY="title";

SmartPlaylist::SmartPlaylist(const std::string& name,const std::vector<std::string>& rules):name(name),rules(rules){}

std::vector<Track*> SmartPlaylist::evaluate(const MediaLibrary* library) const{
    std::vector<Track*> selected;
    for(Track* track:library->getTracks()){
        bool matchesAll=true;
        for(const std::string& rule:rules){
            if(!matchesRule(track,rule)){
                matchesAll=false;
            }
        }
        if(matchesAll){
            selected.push_back(track);
        }
    }
    return selected;
}

bool SmartPlaylist::matchesRule(const Track* track,const std::string& rule) const{
    size_t separator=rule.find(RULE_SEPARATOR);
    if(separator==std::string::npos){
        return false;
    }
    std::string key=rule.substr(0,separator);
    std::string value=rule.substr(separator+1);
    if(key==TITLE_KEY){
        return track->matchesQuery(value);
    }
    try{
        return matchesNumber(track,key,std::stoi(value));
    }catch(const std::logic_error&){
        return false;
    }
}

bool SmartPlaylist::matchesNumber(const Track* track,const std::string& key,int number) const{
    if(key==GENRE_KEY){
        return track->hasGenre(number);
    }
    if(key==ARTIST_KEY){
        return track->getArtistId()==number;
    }
    if(key==MIN_DURATION_KEY){
        return track->getDurationMs()>=number;
    }
    return key==MAX_DURATION_KEY && track->getDurationMs()<=number;
}