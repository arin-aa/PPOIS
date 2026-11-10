#include "AudioFile.h"
#include <algorithm>
#include <vector>

const std::vector<std::string> LOSSLESS_FORMATS={"flac","wav","alac"};

AudioFile::AudioFile(const std::string& uri,const std::string& format,int bitrate,long long sizeBytes):
    uri(uri),format(format),bitrate(bitrate),sizeBytes(sizeBytes){}

bool AudioFile::isLossless() const{
    return std::find(LOSSLESS_FORMATS.begin(),LOSSLESS_FORMATS.end(),format)!=LOSSLESS_FORMATS.end();
}

std::string AudioFile::getExtension() const{
    return "."+format;
}

const std::string& AudioFile::getUri() const{
    return uri;
}

int AudioFile::getBitrate() const{
    return bitrate;
}

long long AudioFile::getSizeBytes() const{
    return sizeBytes;
}