#include "advancedDrawing/texturesDrawing/animTexturesDrawing.h"
#include "advancedDrawing/texturesLoading/animFileTextures.h"
#include "customTypes/caseAnim.h"
#include <cassert>

AnimDrawingData::AnimDrawingData(const AnimLoadData& loadedAnim):
	sprite{ loadedAnim.tload },
	frameDuration{ loadedAnim.frameDuration }
{
	
}

SingleAnimation::SingleAnimation(const AnimTextureElement& animElement)
{
	for( auto const &loaded : animElement )
	{
		singleAnim.emplace_back( AnimDrawingData{ loaded } );
	}
}

size_t SingleAnimation::framesNumber() const
{
	return singleAnim.size();
}

unsigned SingleAnimation::getDuration(size_t index) const
{
	assert( index < singleAnim.size() );
	return singleAnim[index].frameDuration;
}

const AnimDrawingData& SingleAnimation::operator[](size_t index) const
{
	assert( index < singleAnim.size() );
	return singleAnim[index];
}

void SingleAnimation::drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t frameNumber)
{
	assert( frameNumber < singleAnim.size() );
	singleAnim[frameNumber].sprite.draw(rndWnd, position);
}

void SingleAnimation::drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, std::size_t frameNumber)
{
	assert( frameNumber < singleAnim.size() );
	singleAnim[frameNumber].sprite.draw(rndWnd, xpos, ypos);
}

void SingleAnimation::drawFrameToCenter(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t frameNumber)
{
	assert( frameNumber < singleAnim.size() );
	singleAnim[frameNumber].sprite.drawToCenter(rndWnd, position);
}

void SingleAnimation::incrementCurrentFrame(CaseAnim& anim) const
{
	assert( anim.currentFrame < singleAnim.size() );
	if( anim.currentFrame + 1 < singleAnim.size() )
	{
		anim.currentFrame++;
	}
	else{
		anim.currentFrame = 0;
	}
}

AnimTexturesDrawing::AnimTexturesDrawing(const LoadedAnimTexturesList& loadedTexturesList)
{
	if( loadedTexturesList.size() > 0 )
	{
		for( std::size_t i{0} ; i < loadedTexturesList.size() ; ++i )
		{
			animations.emplace_back( SingleAnimation{ loadedTexturesList[i] } );
		}
	}
}

std::size_t AnimTexturesDrawing::size() const
{
	return animations.size();
}

const SingleAnimation& AnimTexturesDrawing::operator[](size_t index) const
{
	assert( index < animations.size() );
	return animations[index];
}

SingleAnimation& AnimTexturesDrawing::operator[](size_t index)
{
	assert( index < animations.size() );
	return animations[index];
}

void AnimTexturesDrawing::drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t animNumber, std::size_t frameNumber)
{
	assert( animNumber < animations.size() );
	animations[animNumber].drawFrame(rndWnd, position, frameNumber);
}

void AnimTexturesDrawing::drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, std::size_t animNumber, std::size_t frameNumber)
{
	assert( animNumber < animations.size() );
	animations[animNumber].drawFrame(rndWnd, xpos, ypos, frameNumber );
}

void AnimTexturesDrawing::drawFrameToCenter(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t animNumber, std::size_t frameNumber)
{
	assert( animNumber < animations.size() );
	animations[animNumber].drawFrameToCenter(rndWnd, position, frameNumber);
}

bool AnimTexturesDrawing::isDataChunkValid(const CaseAnim& animChunk) const
{
	if( animChunk.animIndex > 0 && animChunk.animIndex <= animations.size() )
	{
		if( animChunk.currentFrame < animations[animChunk.getModifiedIndex()].framesNumber() )
		{
			return true;
		}
	}
	return false;
}