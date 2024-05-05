#ifndef SDL2_TTF_FONT_H
#define SDL2_TTF_FONT_H

#include "wrappers/ttfPtrWrapper.h"
#include "fileSystem/fileSystem.h"
#include <string>

class LogFile;

namespace sdl2{

class Font
{
private:
	sdl2::FontPtr font;
			
public:
	Font() = default;
	Font(LogFile& log, const fs::path& fontPath, unsigned fontSize);
	~Font() = default;
	Font( const Font& ) = delete;
	Font& operator= ( const Font& ) = delete;
	Font( Font&& ) = default;
	Font& operator= ( Font&& ) = default;
	
	operator bool () const;
	
	TTF_Font* get() const;
	void reset(LogFile& log, const fs::path& fontPath, unsigned fontSize);
	void outputAnErrorMessage(LogFile& log, const fs::path& fontPath) const;
	void reset();
};

}
#endif //SDL2_TTF_FONT_H