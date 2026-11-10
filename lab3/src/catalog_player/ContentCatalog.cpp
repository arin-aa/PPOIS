#include "ContentCatalog.h"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <set>
#include "MediaLibrary.h"
#include "Track.h"

static std::vector<std::string> splitWords(const std::string& text){
    std::vector<std::string> words;
    std::string word;
    for(unsigned char symbol:text){
        if(std::isalnum(symbol)){
            word+=static_cast<char>(std::tolower(symbol));
        }else if(!word.empty()){
            words.push_back(word);
            word.clear();
        }
    }
    if(!word.empty()){
        words.push_back(word);
    }
    return words;
}

static std::vector<int> lookupPrefix(const std::map<std::string,std::vector<int>>& index,const std::string& prefix){
    std::set<int> trackIds;
    for(const auto& entry:index){
        if(entry.first.compare(0,prefix.size(),prefix)==0){
            trackIds.insert(entry.second.begin(),entry.second.end());
        }
    }
    return std::vector<int>(trackIds.begin(),trackIds.end());
}


ContentCatalog::ContentCatalog(MediaLibrary* library):library(library){}

std::vector<Track*> ContentCatalog::searchByTitle(const std::string& query) const{
    std::vector<std::string> words=splitWords(query);
    std::vector<Track*> found;
    if(words.empty()){
        return found;
    }
    std::vector<int> matched=lookupPrefix(index,words[0]);
    for(size_t position=1;position<words.size();position++){
        std::vector<int> wordMatches=lookupPrefix(index,words[position]);
        std::vector<int> common;
        std::set_intersection(matched.begin(),matched.end(),wordMatches.begin(),wordMatches.end(),std::back_inserter(common));
        matched=common;
    }
    for(Track* track:library->getTracks()){
        if (std::count(matched.begin(), matched.end(), track->getId()) > 0){
            found.push_back(track);
        }
    }
    return found;
}

int ContentCatalog::rebuildIndex(){
    index.clear();
    for(const Track* track:library->getTracks()){
        for(const std::string& word:splitWords(track->getTitle())){
            index[word].push_back(track->getId());
        }
    }
    return static_cast<int>(index.size());
}

MediaLibrary* ContentCatalog::getLibrary() const{
    return library;
}