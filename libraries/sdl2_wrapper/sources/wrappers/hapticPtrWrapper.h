#ifndef WRAPPERS_HAPTIC_PTR_WRAPPER_H
#define WRAPPERS_HAPTIC_PTR_WRAPPER_H

#include "SDL_haptic.h"
#include <memory>

namespace sdl2{
	struct HapticDeleter{
		void operator()(SDL_Haptic* ptr) { if (ptr) SDL_HapticClose(ptr); }
	};
	using HapticPtr	= std::unique_ptr<SDL_Haptic, HapticDeleter>;
}


#endif //WRAPPERS_HAPTIC_PTR_WRAPPER_H