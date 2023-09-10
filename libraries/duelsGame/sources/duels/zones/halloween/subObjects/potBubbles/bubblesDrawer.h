#ifndef BUBBLES_DRAWER_H
#define BUBBLES_DRAWER_H

#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"
#include "customTypes/positionTypes.h"
#include <vector>

struct Essentials;

constexpr std::size_t BubblesFrameNumber = 26;
constexpr std::size_t BubblesClusterNumber = 2;

class BubblesDrawer
{
private:
	std::vector<std::size_t > frameIndex;
	std::vector< Offset > bubblesPosition;
	std::vector< TextureCombo > bubblesTextures;
	AccurateTimeDelay frameDelay;
	
public:
	explicit BubblesDrawer(Essentials& essentials);
	~BubblesDrawer() = default;
	BubblesDrawer( const BubblesDrawer& ) = delete;
	BubblesDrawer& operator= ( const BubblesDrawer& ) = delete;
	BubblesDrawer( BubblesDrawer&& ) = default;
	BubblesDrawer& operator= ( BubblesDrawer&& ) = default;
	
	void drawBubbles(sdl2::RendererWindow& rndWnd);
	void update();

private:
	void animFrame(std::size_t index);
};

#endif //BUBBLES_DRAWER_H