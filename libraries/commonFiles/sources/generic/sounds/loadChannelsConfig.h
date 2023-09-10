#ifndef LOAD_CHANNELS_CONFIG_H
#define LOAD_CHANNELS_CONFIG_H

#include "fileSystem/fileSystem.h"
#include <sstream>

struct AppLogFiles;
struct ChannelData;

namespace loadChanCfg{

void readLines(AppLogFiles& logs, const fs::path& filePath, bool& channelLoadWasPerfect);

void setData(AppLogFiles& logs, const fs::path& filePath, std::istringstream& lineStream, ChannelData& data, bool& channelLoadWasPerfect);

}

#endif //LOAD_CHANNELS_CONFIG_H