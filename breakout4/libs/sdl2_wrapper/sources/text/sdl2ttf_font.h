#ifndef SDL2_TTF_FONT_H
#define SDL2_TTF_FONT_H

#include "wrappers/sdl2_ptr.h"
#include <string>

class LogFile;

namespace sdl2{

class Font
{
private:
	sdl2::FontPtr font;
			
public:
	Font() = default;
	Font(LogFile& log, const std::string& fontPath, unsigned fontSize);
	~Font() = default;
	Font( const Font& ) = delete;
	Font& operator= ( const Font& ) = delete;
	Font( Font&& ) = default;
	Font& operator= ( Font&& ) = default;
	
	operator bool () const;
	
	TTF_Font* get() const;
	void reset(LogFile& log, const std::string& fontPath, unsigned fontSize);
	void outputAnErrorMessage(LogFile& log, const std::string& fontPath) const;
	void reset();
};

}
#endif //SDL2_TTF_FONT_H