/**
 * @file main.cpp
 * @brief Console user interface for the music player application.
 */
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Album.h" 
#include "Artist.h" 
#include "AudioFile.h" 
#include "Genre.h" 
#include "MediaLibrary.h" 
#include "ContentCatalog.h" 
#include "SearchQuery.h" 
#include "SearchService.h" 
#include "Track.h"
#include "AudioEngine.h" 
#include "Equalizer.h" 
#include "PlaybackHistory.h" 
#include "PlaybackState.h" 
#include "Player.h" 
#include "Queue.h" 
#include "SleepTimer.h"
#include "FavoritesCollection.h" 
#include "Playlist.h" 
#include "SmartPlaylist.h" 
#include "Follow.h" 
#include "ListeningActivity.h" 
#include "SharedPlaylist.h" 
#include "UserFeed.h"
#include "AuthenticationService.h" 
#include "Subscription.h" 
#include "User.h" 
#include "CloudStorage.h" 
#include "Device.h" 
#include "DownloadManager.h" 
#include "OfflineCache.h"
#include "SyncConflict.h" 
#include "SyncService.h" 
#include "Lyrics.h" 
#include "MetadataProvider.h" 
#include "RadioStation.h" 
#include "RecommendationService.h" 
#include "TagEditor.h"
#include "MusicPlayerExceptions.h"
using namespace std;

const int MAX_IGNOR=100000;///<Maximum number of characters ignored in the input stream on error.
const int ACTION_WIDTH=50;///<Width of the action name column.
const int RESULT_WIDTH=44;///<Width of the result column.

/** @brief Requests an integer from the user, repeating until the input is valid. */
int readChoice(const string& line){
    int choice;
    while(true){
        cout<<line;
        if(cin>>choice){
            cin.clear(); cin.ignore(MAX_IGNOR,'\n');
            return choice;
        }
        cin.clear(); cin.ignore(MAX_IGNOR,'\n');
        cout<<"Invalid input. Try again.\n";
    }
}
/** @brief Prints the scenario title and the table header. */
void title(int number,const string& name){
    cout<<"\n=== "<<number<<". "<<name<<" ===\n"<<left<<setw(ACTION_WIDTH)<<"Action"<<"Result\n";
    cout<<string(ACTION_WIDTH-2,'-')<<"  "<<string(RESULT_WIDTH,'-')<<"\n";
}
/** @brief Prints one aligned table row. */
void row(const string& action,const string& result){
    cout<<left<<setw(ACTION_WIDTH)<<action<<result<<"\n";
}
/** @brief Prints a numeric, boolean or text result of an action with an optional unit. */
template<typename Value>
void report(const string& action,const Value& value,const string& unit=""){
    ostringstream text;
    text<<boolalpha<<fixed<<setprecision(1)<<value;
    row(action,"done, "+text.str()+unit);
}
/** @brief Runs an action and prints "done" or the text of the domain exception. */
template<typename Action>
void attempt(const string& action,Action run){
    try{
        run();
        row(action,"done");
    }catch(const MusicPlayerException& error){
        row(action,string("ERROR: ")+error.what());
    }
}

/** @brief Scenario 1: catalog of tracks, albums and artists, and search. */
void scenarioCatalog(){
    title(1,"Catalog and search");
    AudioFile mp3("a.mp3","mp3",320,9000000),flac("b.flac","flac",1411,40000000);
    Genre rock(1,"rock"),punk(2,"rock/punk");
    Track song(1,"Bohemian Rhapsody",1,1,355000,&mp3,{1}),radio(2,"Radio Ga Ga",1,1,343000,&flac,{1,2});
    Album album(1,"a night at the opera",1,{1,2,9});
    MediaLibrary library({&song},{&album},{},{&rock,&punk});
    ContentCatalog catalog(&library);SearchService search(&catalog);
    report("Is the FLAC file lossless",flac.isLossless());
    report("Is rock/punk a subgenre of rock",punk.isSubgenreOf(rock));
    report("Add a new track, then the same track again",library.addTrack(&radio)&&!library.addTrack(&radio));
    attempt("Total duration of an album with a missing track",[&]{album.getTotalDuration(&library);});
    report("Rebuild the search index, tracks indexed",catalog.rebuildIndex());
    report("Search 'RADIO!!' in all types, top result",search.search(SearchQuery("RADIO!!")).getTopResult());
    report("Search 'night' among albums only, top result",search.search(SearchQuery("night","album")).getTopResult());
}

/** @brief Scenario 2: queue, player, history, equalizer and sleep timer. */
void scenarioPlayback(){
    title(2,"Playback and queue");
    AudioFile good("a.mp3","mp3",320,1000),corrupted("b.mp3","mp3",0,0);
    Track first(1,"Intro",1,1,180000,&good),second(2,"Verse",1,1,200000,&good),broken(3,"Broken",1,1,100000,&corrupted);
    AudioEngine engine;Queue queue;PlaybackState state;PlaybackHistory history("anna");
    Player player(&engine,&queue,&state,&history);Equalizer equalizer;SleepTimer timer;
    attempt("Play with an empty queue",[&]{player.play();});
    queue.add(&first);queue.add(&second);queue.add(&broken);
    attempt("Play the first track",[&]{player.play();});
    attempt("Seek beyond the end of the track",[&]{player.seek(999999);});
    attempt("Seek to 170 s",[&]{player.seek(170000);});
    attempt("Next track after 170 s of listening",[&]{player.next(170000);});
    attempt("Next track whose audio file is corrupted",[&]{player.next(180000);});
    attempt("Next track at the end of the queue",[&]{player.next(190000);});
    report("Is the last saved session completed",history.getRecent(1)[0].isCompleted());
    attempt("Apply the unknown equalizer preset 'jazz'",[&]{equalizer.applyPreset("jazz");});
    attempt("Start the sleep timer for 0 ms",[&]{timer.start(0);});
}

/** @brief Scenario 3: playlists, favorites, smart playlist and social features. */
void scenarioPlaylists(){
    title(3,"Playlists and social features");
    AudioFile file("a.mp3","mp3",320,1000);
    Track song(1,"Intro",1,1,180000,&file,{1}),epic(2,"Epic",1,1,400000,&file,{1}),silent(3,"Silent",1,1,1000,nullptr);
    MediaLibrary library({&song,&epic});Playlist playlist(1,"anna","Road trip","for the car");
    attempt("Add a track without an audio file",[&]{playlist.addTrack(&silent);});
    playlist.addTrack(&song);playlist.addTrack(&epic);
    report("Total duration of the playlist",playlist.getTotalDuration()/1000," s");
    FavoritesCollection favorites("anna");
    report("Toggle favorite on track 1, is it favorite",favorites.toggle(1,1000));
    SmartPlaylist smart("Long rock",{"genre:1","minDuration:300000"});
    report("Smart playlist 'Long rock', tracks selected",smart.evaluate(&library).size());
    SharedPlaylist shared(&playlist,"anna");
    attempt("Add the owner as a collaborator",[&]{shared.addCollaborator("anna");});
    attempt("Remove Clara who is not a collaborator",[&]{shared.removeCollaborator("clara");});
    Follow follow("boris","anna",0),back("anna","boris",0);
    report("Do Boris and Anna follow each other",follow.isMutual(back));
    ListeningActivity old("anna",&song,1000),fresh("anna",&epic,9000);
    report("Feed of Boris for a 5 s window, items",UserFeed("boris",{&follow}).build({&old,&fresh},10000,5000).size());
}

/** @brief Scenario 4: authentication, subscription and user name. */
void scenarioAccount(){
    title(4,"Account and subscription");
    Subscription premium("Premium",1000,false),family("Family",1000,true);
    User user("u1","anna@mail.com","Anna",&premium);AuthenticationService auth;
    attempt("Sign in without a user",[&]{auth.signIn(nullptr,"password1");});
    attempt("Sign in with the weak password 'abc'",[&]{auth.signIn(&user,"abc");});
    attempt("Sign in with the password 'secret123'",[&]{auth.signIn(&user,"secret123");});
    report("Is the subscription active at moment 500",user.hasActiveSubscription(500));
    report("Is the subscription active at moment 2000",user.hasActiveSubscription(2000));
    attempt("Renew an expired plan without auto-renew",[&]{premium.renew(2000,1000);});
    report("Renew the auto-renewed plan, new expiry",family.renew(2000,1000));
    report("Rename the user to a 40-character name",user.updateDisplayName(string(40,'x')));
    attempt("Six wrong passwords in a row",[&]{for(int i=0;i<6;i++){try{auth.signIn(&user,"x");}catch(const AuthenticationException&){}}});
}

/** @brief Scenario 5: cloud synchronization, downloads and offline cache. */
void scenarioSync(){
    title(5,"Synchronization and offline mode");
    CloudStorage guest("https://cloud.example",""),cloud("https://cloud.example","token");SyncService service(&cloud);
    attempt("Download from the cloud without a token",[&]{guest.download("playlists");});
    attempt("Download before anything was uploaded",[&]{cloud.download("playlists");});
    report("First sync uploads the local version 100",service.sync("playlists",100,"newest"));
    report("Conflict 100 and 250 resolved as 'newest'",SyncConflict("playlists",100,250).applyResolution("newest"));
    attempt("Resolve a conflict with the strategy 'random'",[&]{SyncConflict("playlists",1,2).applyResolution("random");});
    Device phone("d1","Phone","android",0,"token");
    report("Is the phone online after 10 minutes",phone.isOnline(600000));
    DownloadManager downloads(1);
    report("Start the 1st and the 2nd download, 2nd started",downloads.start(1,"https://x/1.mp3")&&downloads.start(2,"https://x/2.mp3"));
    attempt("Start a download without an address",[&]{downloads.start(3,"");});
    OfflineCache cache(100,1000);
    cache.put(1,60,0);cache.put(2,60,10);
    attempt("Read track 1 pushed out by track 2",[&]{cache.get(1,20);});
    report("Read track 2 from the cache, size",cache.get(2,20)," bytes");
    attempt("Read track 2 after its time to live",[&]{cache.get(2,5000);});
    attempt("Cache a file bigger than the cache",[&]{cache.put(3,500,0);});
}

/** @brief Scenario 6: lyrics, metadata, tags, radio and recommendations. */
void scenarioExtras(){
    title(6,"Lyrics, tags and recommendations");
    Lyrics lyrics(1,{TimedLyric(0,"Is this the real life?"),TimedLyric(5000,"Is this just fantasy?")},"lrc");
    report("Lyrics line at the 6th second",lyrics.getLineAt(6000));
    attempt("Lyrics with lines in a wrong time order",[&]{Lyrics bad(1,{TimedLyric(5000,"b"),TimedLyric(0,"a")},"lrc");});
    MetadataProvider api("https://meta.example"),offline("");
    report("Title from the file name queen_radio_ga_ga.mp3",api.fetchMetadata("music/queen_radio_ga_ga.mp3")["title"]);
    attempt("Fetch metadata while the service is offline",[&]{offline.fetchMetadata("music/a.mp3");});
    TagEditor tags;
    report("Artist tag of 'Queen - Radio Ga Ga.mp3'",tags.readTags("music/Queen - Radio Ga Ga.mp3")["artist"]);
    attempt("Write tags without a title",[&]{tags.writeTags("music/old.mp3",{{"artist","Queen"}});});
    report("Genre of 'Classic Rock FM' from a list",RadioStation("Classic Rock FM","https://r.fm").classifyGenre({"jazz","rock"}));
    attempt("Tune in to a station with the ftp address",[&]{RadioStation("Rock FM","ftp://r.fm").tuneIn();});
    AudioFile file("a.mp3","mp3",320,1000);
    Track song(1,"Intro",1,1,180000,&file,{1}),epic(2,"Epic",1,1,400000,&file,{1});
    MediaLibrary library({&song,&epic});PlaybackHistory history("anna");
    PlaybackSession session(&song,0);session.finish(1000);history.add(session);
    RecommendationService recommender(&history,&library);
    report("Recommendations after listening to rock",recommender.recommendFor(5).size());
    attempt("Tracks similar to the unknown track 99",[&]{recommender.similarTracks(99,3);});
}

/** @brief Program entry point: shows the menu of 6 scenarios and handles invalid input. */
int main(){
    while(true){
        cout<<"\nMenu\n1 - Catalog and search.\n2 - Playback and queue.\n3 - Playlists and social features.\n"
              "4 - Account and subscription.\n5 - Synchronization and offline mode.\n6 - Lyrics, tags and recommendations.\n0 - Exit.\n";
        int choice=readChoice("Your choice: ");cout<<endl;
        switch(choice){
            case 1: scenarioCatalog(); break;
            case 2: scenarioPlayback(); break;
            case 3: scenarioPlaylists(); break;
            case 4: scenarioAccount(); break;
            case 5: scenarioSync(); break;
            case 6: scenarioExtras(); break;
            case 0: cout<<"Exit.\n"; return 0;
            default: cout<<"Invalid choice.\n";
        }
    }
}