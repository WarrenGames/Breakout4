#ifndef GAME_RECT_LOADER_H
#define GAME_RECT_LOADER_H

#include "SDL_rect.h"
#include <vector>
#include <string>

struct Essentials;

class RectLoader
{
private:
	std::vector< SDL_Rect > rects;
	bool isLoadingPerfect;

public:
	explicit RectLoader(Essentials& essentials, std::size_t vectorSize, const std::string& rectsFile, unsigned rectId);
	~RectLoader() = default;
	RectLoader( const RectLoader& ) = delete;
	RectLoader& operator= ( const RectLoader& ) = delete;
	RectLoader( RectLoader&& ) = default;
	RectLoader& operator= ( RectLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	const SDL_Rect& getRect(std::size_t index) const;
	
private:
	void openFileForLoading(Essentials& essentials, const std::string& rectsFile, unsigned rectId);
};

#endif //GAME_RECT_LOADER_H