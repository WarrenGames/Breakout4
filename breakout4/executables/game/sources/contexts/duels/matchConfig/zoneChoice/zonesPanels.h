#ifndef DUELS_ZONES_PANELS_GUI_H
#define DUELS_ZONES_PANELS_GUI_H

#include "texturing/texturesCombo.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
namespace duels{

class PanelsGraphics
{
private:
	bool isLoadingPerfect;
	std::array< SDL_Rect, duels::ZONE_MAX > panelsFrames;
	std::array< TextureCombo, duels::ZONE_MAX > zonesPanels;

public:
	explicit PanelsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~PanelsGraphics() = default;
	PanelsGraphics( const PanelsGraphics& ) = delete;
	PanelsGraphics& operator= ( const PanelsGraphics& ) = delete;
	PanelsGraphics( PanelsGraphics&& ) = default;
	PanelsGraphics& operator= ( PanelsGraphics&& ) = default;
	
	operator bool () const;
	
	void drawPanels(sdl2::RendererWindow& rndWnd) const;
	
	bool setZoneChoice(const Offset& mousePosition, bool leftButtonState, unsigned& zoneIndex) const;

private:
	void drawPictures(sdl2::RendererWindow& rndWnd) const;
	void drawFrames(sdl2::RendererWindow& rndWnd) const;
};

}
#endif //DUELS_ZONES_PANELS_GUI_H