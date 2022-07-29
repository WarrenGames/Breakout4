#include "contexts/duels/matchConfig/graphics/spinAnimation.h"
#include "texturing/texturePosition.h"
#include "customTypes/positionTypes.h"
#include "consts/constexprScreen.h"

constexpr std::size_t SPIN_FRAME_NUM = 24;

SpinAnim::SpinAnim(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	isLoadingPerfect{true},
	index{0},
	delay{}
{
	for( std::size_t i{0} ; i < SPIN_FRAME_NUM ; ++i )
	{
		spinTextures.emplace_back(TextureCombo{logs, rndWnd, "textures/sprites/spin/spin_" + std::to_string(i) + ".png", 
									TexturePosition{SQR_SIZE*12, SQR_SIZE*8} } );
		if( false == spinTextures.back().texture )
		{
			isLoadingPerfect = false;
		}
	}
}

SpinAnim::operator bool() const
{
	return isLoadingPerfect;
}

void SpinAnim::update()
{
	if( delay.hasTimeElapsed( std::chrono::milliseconds{1500 / SPIN_FRAME_NUM} ) )
	{
		if( index < spinTextures.size() - 1 )
		{
			index++;
		}
		else{
			index = 0;
		}
		delay.joinTimePoints();
	}
}

void SpinAnim::drawSpin(sdl2::RendererWindow& rndWnd, const Offset& pos)
{
	if( index < spinTextures.size() && spinTextures[index].texture )
	{
		spinTextures[index].draw(rndWnd, pos);
	}
}
