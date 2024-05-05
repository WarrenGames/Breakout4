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
	explicit MixerModule(LogFile& log, unsigned customChannelsNumber);
	~MixerModule();
	MixerModule( const MixerModule& ) = delete;
	MixerModule& operator= ( const MixerModule& ) = delete;
	MixerModule( MixerModule&& ) = default;
	MixerModule& operator= ( MixerModule&& ) = default;
	
	operator bool() const;
	bool wasLoadingPerfect() const;
	
	void initSdl2Mixer(LogFile& log, unsigned customChannelsNumber);
};

}

#endif //SDL2_MIXER_MODULE_INIT_H