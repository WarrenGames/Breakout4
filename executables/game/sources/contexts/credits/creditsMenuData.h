#ifndef CREDITS_MENU_DATA_H
#define CREDITS_MENU_DATA_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"
#include <vector>

struct Essentials;

namespace creditsMenu{
	
class GraphicsData 
{
private:
	TextsBlocks texts;
	sdl2::Font arial;
	std::vector< TextureCombo > graphicsTexts;

public:
	explicit GraphicsData(Essentials& essentials);
	~GraphicsData() = default;
	GraphicsData( const GraphicsData& ) = delete;
	GraphicsData& operator= ( const GraphicsData& ) = delete;
	GraphicsData( GraphicsData&& ) = default;
	GraphicsData& operator= ( GraphicsData&& ) = default;
	
	void drawEverything(Essentials& essentials) const;
};

}

#endif //CREDITS_MENU_DATA_H