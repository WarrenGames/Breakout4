#ifndef H_SONS_CHARGEMENT
#define H_SONS_CHARGEMENT

#include "fileSystem/fileSystem.h"
#include "SDL_mixer.h"

class LogFile;

Mix_Chunk* loadSoundChunk(LogFile& log, const fs::path& soundPath);

Mix_Music* loadMixMusic(LogFile& log, const fs::path& musicPath);

#endif // H_SONS_CHARGEMENT

