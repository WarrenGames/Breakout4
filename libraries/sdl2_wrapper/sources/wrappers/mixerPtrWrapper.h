#ifndef WRAPPERS_MIXER_PTR_WRAPPER_H
#define WRAPPERS_MIXER_PTR_WRAPPER_H

#include "SDL_mixer.h"
#include <memory>

namespace sdl2{
	struct MixerDeleter{
		void operator()(Mix_Chunk* ptr) { if (ptr) Mix_FreeChunk(ptr); }
		void operator()(Mix_Music* ptr) { if (ptr) Mix_FreeMusic(ptr); }
	};
	using Mix_ChunkPtr = std::unique_ptr<Mix_Chunk,	MixerDeleter>;
	using Mix_MusicPtr = std::unique_ptr<Mix_Music,	MixerDeleter>;
}

#endif //WRAPPERS_MIXER_PTR_WRAPPER_H