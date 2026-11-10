#include "SmartPlaylist.h"
#include <algorithm>
#include <stdexcept>
#include "MediaLibrary.h"
#include "Track.h"

const char RULE_SEPARATOR=':';
const std::string GENRE_KEY="genre";
const std::string ARTIST_KEY="artist";
const std::string MIN_DURATION_KEY="minDuration";
const std::string MAX_DURATION_KEY="maxDuration";
const std::string TITLE_KEY="title";

namespace{
bool matchesNumber(const Track* track,const std::string& key,int number){
    if(key==GENRE_KEY){
        const std::vector<int>& genreIds=track->getGenreIds();
        return std::find(genreIds.begin(),genreIds.end(),number)!=genreIds.end();
    }
    if(key==ARTIST_KEY){
        return track->getArtistId()==number;
    }
    if(key==MIN_DURATION_KEY){
        return track->getDurationMs()>=number;
    }
    return key==MAX_DURATION_KEY && track->getDurationMs()<=number;
}
}

SmartPlaylist::SmartPlaylist(const std::string& name,const std::vector<std::string>& rules):name(name),rules(rules){}

std::vector<Track*> SmartPlaylist::evaluate(const MediaLibrary* library) const{
    std::vector<Track*> selected;
    for(Track* track:library->getTracks()){
        bool matchesAll=std::all_of(rules.begin(),rules.end(),[&](const std::string& rule){
            return matchesRule(track,rule);
        });
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