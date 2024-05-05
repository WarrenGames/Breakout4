#ifndef SDL2_TTF_MODULE_INIT_H
#define SDL2_TTF_MODULE_INIT_H

class LogFile;

namespace sdl2{
	
class TTFModule
{
private:
	bool isTTFinitialized;
	
public:
	explicit TTFModule(LogFile& log);
	~TTFModule();
	TTFModule( const TTFModule& ) = delete;
	TTFModule& operator= ( const TTFModule& ) = delete;
	TTFModule( TTFModule&& ) = default;
	TTFModule& operator= ( TTFModule&& ) = default;

	bool wasLoadingPerfect() const;
};
	
}

#endif //SDL2_TTF_MODULE_INIT_H