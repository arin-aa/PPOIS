#include "AudioFile.h"
#include <vector>

const std::vector<std::string> LOSSLESS_FORMATS={"flac","wav","alac"};
const std::string EXTENSION_PREFIX=".";

AudioFile::AudioFile(const std::string& uri,const std::string& format,int bitrate,long long sizeBytes):
    uri(uri),format(format),bitrate(bitrate),sizeBytes(sizeBytes){}

bool AudioFile::isLossless() const{
    for(const std::string& losslessFormat:LOSSLESS_FORMATS){
        if(format==losslessFormat){
            return true;
        }
    }
    return false;
}

std::string AudioFile::getExtension() const{
    return EXTENSION_PREFIX+format;
}

const std::string& AudioFile::getUri() const{
    return uri;
}

int AudioFile::getBitrate() const{
    return bitrate;
}