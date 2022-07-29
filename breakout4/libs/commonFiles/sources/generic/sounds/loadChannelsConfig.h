#ifndef LOAD_CHANNELS_CONFIG_H
#define LOAD_CHANNELS_CONFIG_H

#include <string>
#include <sstream>

class LogFile;
struct ChannelData;

namespace loadChanCfg{

void readLines(LogFile& log, const std::string& filePath, bool& channelLoadWasPerfect);

void setData(LogFile& log, const std::string& filePath, std::istringstream& lineStream, ChannelData& data, bool& channelLoadWasPerfect);

}

#endif //LOAD_CHANNELS_CONFIG_H