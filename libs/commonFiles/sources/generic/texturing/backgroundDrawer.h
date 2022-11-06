#ifndef BACKGROUND_DRAWER_H
#define BACKGROUND_DRAWER_H

#include "texturing/texturesCombo.h"
#include "customTypes/positionTypes.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class BackgroundDrawer
{
private:
	bool isLoadingPerfect;
	Offset drawingRepeat;
	TextureCombo texture;

public:
	explicit BackgroundDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, int x_repeat, int y_repeat);
	~BackgroundDrawer() = default;
	BackgroundDrawer( const BackgroundDrawer& ) = delete;
	BackgroundDrawer& operator= ( const BackgroundDrawer& ) = delete;
	BackgroundDrawer( BackgroundDrawer&& ) = default;
	BackgroundDrawer& operator= ( BackgroundDrawer&& ) = default;
	
	operator bool () const;
	
	void drawBackground(sdl2::RendererWindow& rndWnd);
};

#endif //BACKGROUND_DRAWER_H