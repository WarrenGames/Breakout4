#ifndef DUELS_ZONES_PANEL_H
#define DUELS_ZONES_PANEL_H

#include "texturing/rendererWindow.h"
#include "texturing/texturesCombo.h"
#include <vector>

struct AppLogFiles;

class ZonesPanels
{
private:
	std::vector< TextureCombo > panels;//Size should be equal to 'duels::ZoneMax'

public:
	explicit ZonesPanels(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~ZonesPanels() = default;
	ZonesPanels( const ZonesPanels& ) = delete;
	ZonesPanels& operator= ( const ZonesPanels& ) = delete;
	ZonesPanels( ZonesPanels&& ) = default;
	ZonesPanels& operator= ( ZonesPanels&& ) = default;
	
	bool wasLoadingPerfect() const;
	void drawPanel(sdl2::RendererWindow& rndWnd, std::size_t panelIndex) const;
	bool isMouseOverCurrentPanel(const Offset& mousePosition, std::size_t panelIndex) const;
	
private:
	void setAllTexturesPositions();
};

#endif //DUELS_ZONES_PANEL_H