#ifndef DUELS_ZONES_PANEL_H
#define DUELS_ZONES_PANEL_H

#include "texturing/rendererWindow.h"
#include "texturing/texturesCombo.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>

struct AppLogFiles;

class ZonesPanels
{
private:
	bool isLoadingPerfect;
	std::array< TextureCombo, duels::ZONE_MAX > panels;
	
public:
	explicit ZonesPanels(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, int center_x_pos, int center_y_pos);
	~ZonesPanels() = default;
	ZonesPanels( const ZonesPanels& ) = delete;
	ZonesPanels& operator= ( const ZonesPanels& ) = delete;
	ZonesPanels( ZonesPanels&& ) = default;
	ZonesPanels& operator= ( ZonesPanels&& ) = default;
	
	bool wasLoadingPerfect() const;
	void drawPanel(sdl2::RendererWindow& rndWnd, std::size_t panelIndex) const;
	bool isMouseOverCurrentPanel(const Offset& mousePosition, std::size_t panelIndex) const;
};

#endif //DUELS_ZONES_PANEL_H