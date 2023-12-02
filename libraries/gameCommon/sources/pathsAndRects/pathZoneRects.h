#ifndef PATHS_RECT_LOADER_H
#define PATHS_RECT_LOADER_H

#include "fileSystem/fileSystem.h"
#include "SDL_rect.h"
#include <vector>
#include <iosfwd>

struct AppLogFiles;

class ZonesRectsLoader
{
private:
	std::vector< SDL_Rect > rects;
	bool isLoadingPerfect;

public:
	explicit ZonesRectsLoader(AppLogFiles& logs, const fs::path& rectsFilePath);
	~ZonesRectsLoader() = default;
	ZonesRectsLoader( const ZonesRectsLoader& ) = delete;
	ZonesRectsLoader& operator= ( const ZonesRectsLoader& ) = delete;
	ZonesRectsLoader( ZonesRectsLoader&& ) = default;
	ZonesRectsLoader& operator= ( ZonesRectsLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	std::vector< SDL_Rect >::const_iterator cbegin() const;
	std::vector< SDL_Rect >::const_iterator cend() const;
	
private:
	void openFile(AppLogFiles& logs, const fs::path& rectsFilePath);
	void readSquareSizeRelativeRectsValues(AppLogFiles& logs, std::ifstream& rectsFile, const fs::path& rectsFilePath, std::size_t& fileLineNumber);
};

#endif //PATHS_RECT_LOADER_H