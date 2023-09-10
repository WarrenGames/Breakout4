#ifndef DUELS_ZONES_PANELS_GUI_H
#define DUELS_ZONES_PANELS_GUI_H

#include "texturing/texturesCombo.h"
#include <vector>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
namespace duels{

class PanelsGraphics
{
private:
	std::vector< TextureCombo > zonesPanels;

public:
	explicit PanelsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~PanelsGraphics() = default;
	PanelsGraphics( const PanelsGraphics& ) = delete;
	PanelsGraphics& operator= ( const PanelsGraphics& ) = delete;
	PanelsGraphics( PanelsGraphics&& ) = default;
	PanelsGraphics& operator= ( PanelsGraphics&& ) = default;
	
	operator bool () const;
	
	void drawPanels(sdl2::RendererWindow& rndWnd) const;
	
	bool setZoneChoice(const Offset& mousePosition, bool leftButtonState, std::size_t& zoneIndex) const;

private:
	void drawPictures(sdl2::RendererWindow& rndWnd) const;
	void drawFrames(sdl2::RendererWindow& rndWnd) const;
};

}
#endif //DUELS_ZONES_PANELS_GUI_H