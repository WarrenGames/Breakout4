#ifndef SDL2_MODULE_INIT_H
#define SDL2_MODULE_INIT_H

#include "SDL.h"

class LogFile;

namespace sdl2{

class ModuleInit
{
private:
	bool isSDL2initialized;

public:
	explicit ModuleInit(Uint32 flags, LogFile& log);
	~ModuleInit();
	ModuleInit( const ModuleInit& ) = delete;
	ModuleInit& operator= ( const ModuleInit& ) = delete;
	ModuleInit( ModuleInit&& ) = default;
	ModuleInit& operator= ( ModuleInit&& ) = default;
	
	bool wasLoadingPerfect() const;
};

}

#endif //SDL2_MODULE_INIT_H