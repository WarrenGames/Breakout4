#ifndef H_SONS_CHARGEMENT
#define H_SONS_CHARGEMENT

#include "SDL_mixer.h"
#include <string>

class LogFile;

Mix_Chunk* loadSoundChunk(LogFile& log, const std::string& soundPath);

Mix_Music* loadMixMusic(LogFile& log, const std::string& musicPath);

#endif // H_SONS_CHARGEMENT

