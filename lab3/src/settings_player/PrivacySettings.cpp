#include "PrivacySettings.h"

PrivacySettings::PrivacySettings(bool shareListening,bool publicPlaylists):
    shareListening(shareListening),publicPlaylists(publicPlaylists){}

bool PrivacySettings::isPrivate() const{
    return !shareListening && !publicPlaylists;
}