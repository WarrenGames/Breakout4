#ifndef SDL2_MIXER_MODULE_INIT_H
#define SDL2_MIXER_MODULE_INIT_H

class LogFile;

namespace sdl2{

class MixerModule
{
private:
	bool isMixerInitialized;

public:
	explicit MixerModule(LogFile& log);
	~MixerModule();
	MixerModule( const MixerModule& ) = delete;
	MixerModule& operator= ( const MixerModule& ) = delete;
	MixerModule( MixerModule&& ) = default;
	MixerModule& operator= ( MixerModule&& ) = default;
	
	bool wasLoadingPerfect() const;
};

}

#endif //SDL2_MIXER_MODULE_INIT_H