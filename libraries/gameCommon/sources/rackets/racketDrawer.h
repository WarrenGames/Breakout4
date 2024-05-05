#ifndef DUELS_RAQUETTE_DRAWER_H
#define DUELS_RAQUETTE_DRAWER_H

#include "texturing/texturesCombo.h"
#include <vector>
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct Offset;

enum{ RacketIsBlue, RacketIsRed, RacketIsGreen, FrozenBlueRacket };

class RacketDrawer
{
private:
	std::vector< TextureCombo > racketTextures;
	std::vector< int > racketWidth;
	bool isLoadingPerfect;

public:
	explicit RacketDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType);
	~RacketDrawer() = default;
	RacketDrawer( const RacketDrawer& ) = delete;
	RacketDrawer& operator= ( const RacketDrawer& ) = delete;
	RacketDrawer( RacketDrawer&& ) = default;
	RacketDrawer& operator= ( RacketDrawer&& ) = default;
	
	bool wasLoadingPerfect() const;
	void browseTexturesForErrors();
	void loadRacket(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType);
	void loadRacketTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& textureSuffix);
	void loadFrozenBlueRacket(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	void fillWidthData(AppLogFiles& logs);
	int getWidth(std::size_t index) const;
	int getHeight(std::size_t index) const;
	
	void drawRacket( sdl2::RendererWindow& rndWnd, std::size_t racketSize, const Offset& racketPos );
};

#endif //DUELS_RAQUETTE_DRAWER_H