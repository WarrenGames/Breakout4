#include "contexts/duels/zones/halloween/subObjects/potBubbles/bubblesDrawer.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include <cassert>

BubblesDrawer::BubblesDrawer(Essentials& essentials):
	frameIndex{0, BubblesFrameNumber / 2},
	bubblesPosition{{ {7*SQR_SIZE- 44 , 5*SQR_SIZE - SQR_SIZE * 3 / 2 + 13}, {13*SQR_SIZE - 44, 5*SQR_SIZE - SQR_SIZE * 3 / 2 + 13} }},
	frameDelay{}
{
	for( std::size_t i{0} ; i < BubblesFrameNumber ; ++i )
	{
		bubblesTextures.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, "textures/sprites/bubbles/animBubbles_" + std::to_string(i) + ".png"} );	
	}
}

void BubblesDrawer::drawBubbles(sdl2::RendererWindow& rndWnd)
{
	for(std::size_t i{0} ; i < BubblesClusterNumber ; ++i )
	{
		bubblesTextures[frameIndex[i]].draw(rndWnd, bubblesPosition[i] );
	}
}

void BubblesDrawer::update()
{
	if( frameDelay.hasTimeElapsed( std::chrono::milliseconds{30} ) )
	{
		animFrame(0);
		animFrame(1);
		frameDelay.joinTimePoints();
	}
}

void BubblesDrawer::animFrame(std::size_t index)
{
	assert( index < frameIndex.size() );
	if( frameIndex[index] + 1 < BubblesFrameNumber )
		frameIndex[index]++;
	else
		frameIndex[index] = 0;
}