#ifndef WRAPPERS_TTF_PTR_WRAPPER_H
#define WRAPPERS_TTF_PTR_WRAPPER_H

#include "SDL_ttf.h"
#include <memory>

namespace sdl2{
	struct TTFDeleter{
		void operator()(TTF_Font* ptr) { if (ptr) TTF_CloseFont(ptr); }
	};
	using FontPtr = std::unique_ptr<TTF_Font, TTFDeleter>;
}

#endif //WRAPPERS_TTF_PTR_WRAPPER_H