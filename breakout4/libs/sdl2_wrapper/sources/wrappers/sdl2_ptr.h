#ifndef H_UNIQ_PTR_SDL
#define H_UNIQ_PTR_SDL

#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_joystick.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_haptic.h"
#include <memory>
 
namespace sdl2{
	struct SDL_Deleter {
		void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_RWops*	ptr) { if (ptr) SDL_RWclose(ptr); }
		void operator()(SDL_Joystick* ptr) { if (ptr) SDL_JoystickClose(ptr); }
		void operator()(TTF_Font*	 ptr) { if (ptr) TTF_CloseFont(ptr); }
		void operator()(Mix_Chunk*	ptr) { if (ptr) Mix_FreeChunk(ptr); }
		void operator()(Mix_Music*	ptr) { if (ptr) Mix_FreeMusic(ptr); }
		void operator()(SDL_Haptic*   ptr) { if (ptr) SDL_HapticClose(ptr); }
	};
	using WindowPtr	= std::unique_ptr<SDL_Window,   SDL_Deleter>;
	using RendererPtr  = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
	using SurfacePtr   = std::unique_ptr<SDL_Surface,  SDL_Deleter>;
	using TexturePtr   = std::unique_ptr<SDL_Texture,  SDL_Deleter>;
	using RWopsPtr	 = std::unique_ptr<SDL_RWops,	SDL_Deleter>;
	using JoystickPtr  = std::unique_ptr<SDL_Joystick, SDL_Deleter>;
	using FontPtr	  = std::unique_ptr<TTF_Font,	 SDL_Deleter>;
	using Mix_ChunkPtr = std::unique_ptr<Mix_Chunk,	SDL_Deleter>;
	using Mix_MusicPtr = std::unique_ptr<Mix_Music,	SDL_Deleter>;
	using HapticPtr	= std::unique_ptr<SDL_Haptic,   SDL_Deleter>;
}

#endif // H_UNIQ_PTR_SDL
