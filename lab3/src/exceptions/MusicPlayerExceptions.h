/**
 * @file MusicPlayerExceptions.h
 * @brief Hierarchy of custom exceptions of the music player domain.
 */
#pragma once
#include <stdexcept>
#include <string>

const int CAPTCHA_ATTEMPTS=3;///<Number of failed attempts after which a captcha is required.
const int FATAL_ENGINE_CODE=500;///<Engine error codes from this value are fatal.
const int START_POSITION_MS=0;///<Position of the beginning of a track (ms).
const int LOCAL_TRACK_ID_START=1000000;///<Identifiers from this value belong to local files.
const long long RENEWAL_GRACE_MS=2592000000LL;///<Thirty days during which a subscription can be renewed.

const std::string LOCKOUT_REASON="lockout";///<Reason used when the account is locked after many attempts.
const std::string FULL_SYNC_ENTITY="library";///<Entity type that can only be repaired by a full sync.
const std::string OFFLINE_SOURCE="offline";///<Metadata source that never has cached data.

/**
 * @class MusicPlayerException
 * @brief Base class for all exceptions of the domain.
 *
 * Inherits std::runtime_error, so every domain error can be caught
 * with one catch (const MusicPlayerException&) block.
 */
class MusicPlayerException:public std::runtime_error{
public:
/**
 * @brief Constructor with a message.
 * @param message Error text.
 */
    explicit MusicPlayerException(const std::string& message):std::runtime_error(message){}
};

/**
 * @class AuthenticationException
 * @brief Exception for a failed sign-in.
 */
class AuthenticationException:public MusicPlayerException{
private:
    int attempts;///<Number of failed attempts so far.

public:
/**
 * @brief Constructor with a message and the number of attempts.
 * @param message Error text.
 * @param attempts Number of failed attempts so far.
 */
    AuthenticationException(const std::string& message,int attempts):
        MusicPlayerException(message),attempts(attempts){}

/**
 * @brief Tells whether the user must solve a captcha before the next attempt.
 * @return true if the attempts reached the captcha threshold.
 */
    bool requiresCaptcha() const{return attempts>=CAPTCHA_ATTEMPTS;}
};

/**
 * @class UserNotFoundException
 * @brief Exception for a user that cannot be found.
 */
class UserNotFoundException:public MusicPlayerException{
private:
    std::string userId;///<Identifier or email that was searched.

public:
/**
 * @brief Constructor with a message and the searched identifier.
 * @param message Error text.
 * @param userId Identifier or email that was searched.
 */
    UserNotFoundException(const std::string& message,const std::string& userId):
        MusicPlayerException(message),userId(userId){}

/**
 * @brief Tells whether the failure is temporary.
 * @return true if the lookup had no identifier, so it may succeed with a valid one.
 */
    bool isTransient() const{return userId.empty();}
};

/**
 * @class InvalidPasswordException
 * @brief Exception for a rejected password.
 */
class InvalidPasswordException:public MusicPlayerException{
private:
    std::string reason;///<Short reason of the rejection.

public:
/**
 * @brief Constructor with a message and a reason.
 * @param message Error text.
 * @param reason Short reason of the rejection.
 */
    InvalidPasswordException(const std::string& message,const std::string& reason):
        MusicPlayerException(message),reason(reason){}

/**
 * @brief Tells whether the account is locked.
 * @return true if the reason is a lockout.
 */
    bool isLockout() const{return reason==LOCKOUT_REASON;}
};

/**
 * @class SubscriptionExpiredException
 * @brief Exception for a subscription that has expired.
 */
class SubscriptionExpiredException:public MusicPlayerException{
private:
    long long expiresAt;///<Moment when the subscription expired (ms).

public:
/**
 * @brief Constructor with a message and the expiration time.
 * @param message Error text.
 * @param expiresAt Moment when the subscription expired (ms).
 */
    SubscriptionExpiredException(const std::string& message,long long expiresAt):
        MusicPlayerException(message),expiresAt(expiresAt){}

/**
 * @brief Tells whether the subscription can still be renewed.
 * @param now Current time (ms).
 * @return true if the grace period after the expiration has not passed.
 */
    bool isRenewable(long long now) const{return now-expiresAt<=RENEWAL_GRACE_MS;}
};

/**
 * @class TrackNotFoundException
 * @brief Exception for a track that is missing in a collection.
 */
class TrackNotFoundException:public MusicPlayerException{
private:
    int trackId;///<Identifier of the missing track.

public:
/**
 * @brief Constructor with a message and a track identifier.
 * @param message Error text.
 * @param trackId Identifier of the missing track.
 */
    TrackNotFoundException(const std::string& message,int trackId):
        MusicPlayerException(message),trackId(trackId){}

/**
 * @brief Tells whether the missing track is a local file.
 * @return true if the identifier belongs to the local range.
 */
    bool isLocalOnly() const{return trackId>=LOCAL_TRACK_ID_START;}
};

/**
 * @class PlaybackException
 * @brief Exception for a playback that cannot continue.
 */
class PlaybackException:public MusicPlayerException{
private:
    int positionMs;///<Playback position at the moment of the failure (ms).

public:
/**
 * @brief Constructor with a message and a position.
 * @param message Error text.
 * @param positionMs Playback position at the moment of the failure (ms).
 */
    PlaybackException(const std::string& message,int positionMs):
        MusicPlayerException(message),positionMs(positionMs){}

/**
 * @brief Tells whether playback can be resumed from the saved position.
 * @return true if some part of the track was already played.
 */
    bool canResume() const{return positionMs>0;}
};

/**
 * @class AudioEngineException
 * @brief Exception for a failure of the audio engine.
 */
class AudioEngineException:public MusicPlayerException{
private:
    int errorCode;///<Engine-specific error code.

public:
/**
 * @brief Constructor with a message and an engine code.
 * @param message Error text.
 * @param errorCode Engine-specific error code.
 */
    AudioEngineException(const std::string& message,int errorCode):
        MusicPlayerException(message),errorCode(errorCode){}

/**
 * @brief Tells whether the engine must be restarted.
 * @return true if the engine code is in the fatal range.
 */
    bool isFatal() const{return errorCode>=FATAL_ENGINE_CODE;}
};

/**
 * @class PlaylistException
 * @brief Exception for a playlist operation that is not allowed.
 */
class PlaylistException:public MusicPlayerException{
private:
    int playlistId;///<Identifier of the playlist.

public:
/**
 * @brief Constructor with a message and a playlist identifier.
 * @param message Error text.
 * @param playlistId Identifier of the playlist.
 */
    PlaylistException(const std::string& message,int playlistId):
        MusicPlayerException(message),playlistId(playlistId){}

/**
 * @brief Tells whether the user can fix the problem and try again.
 * @return true if the playlist identifier is valid.
 */
    bool isRecoverable() const{return playlistId>=0;}
};

/**
 * @class SyncException
 * @brief Exception for a failed synchronization with the cloud.
 */
class SyncException:public MusicPlayerException{
private:
    std::string entityType;///<Type of the entity that failed to sync.

public:
/**
 * @brief Constructor with a message and an entity type.
 * @param message Error text.
 * @param entityType Type of the entity that failed to sync.
 */
    SyncException(const std::string& message,const std::string& entityType):
        MusicPlayerException(message),entityType(entityType){}

/**
 * @brief Tells whether the whole library must be synchronized again.
 * @return true if the failed entity is the library.
 */
    bool requiresFullSync() const{return entityType==FULL_SYNC_ENTITY;}
};

/**
 * @class DownloadException
 * @brief Exception for a track that cannot be downloaded.
 */
class DownloadException:public MusicPlayerException{
private:
    std::string url;///<Address of the file.

public:
/**
 * @brief Constructor with a message and an address.
 * @param message Error text.
 * @param url Address of the file.
 */
    DownloadException(const std::string& message,const std::string& url):
        MusicPlayerException(message),url(url){}

/**
 * @brief Tells whether the download is worth repeating.
 * @return true if the address is known.
 */
    bool shouldRetry() const{return !url.empty();}
};

/**
 * @class MetadataException
 * @brief Exception for metadata that cannot be read or written.
 */
class MetadataException:public MusicPlayerException{
private:
    std::string source;///<Source of the metadata.

public:
/**
 * @brief Constructor with a message and a source.
 * @param message Error text.
 * @param source Source of the metadata.
 */
    MetadataException(const std::string& message,const std::string& source):
        MusicPlayerException(message),source(source){}

/**
 * @brief Tells whether an answer from this source can be cached.
 * @return true unless the source is offline.
 */
    bool isCacheable() const{return source!=OFFLINE_SOURCE;}
};