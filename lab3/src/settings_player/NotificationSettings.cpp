#include "NotificationSettings.h"

NotificationSettings::NotificationSettings(bool enabled,bool newReleases):enabled(enabled),newReleases(newReleases){}

void NotificationSettings::muteAll(){
    enabled=false;
    newReleases=false;
}