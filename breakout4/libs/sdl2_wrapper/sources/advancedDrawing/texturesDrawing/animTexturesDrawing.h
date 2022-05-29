#ifndef ANIM_TEXTURES_DRAWING_H
#define ANIM_TEXTURES_DRAWING_H

#include "texturing/sdl2_sprite.h"
#include <vector>

struct AnimLoadData;
class AnimTextureElement;
namespace sdl2{ class RendererWindow; }
class LoadedAnimTexturesList;
struct CaseAnim;

struct AnimDrawingData
{
	sdl2::Sprite sprite;
	unsigned frameDuration;
	
	explicit AnimDrawingData(const AnimLoadData& loadedAnim);
	~AnimDrawingData() = default;
	AnimDrawingData( const AnimDrawingData& ) = delete;
	AnimDrawingData& operator= ( AnimDrawingData& ) = delete;
	AnimDrawingData( AnimDrawingData&& ) = default;
	AnimDrawingData& operator= ( AnimDrawingData&& ) = default;
};

class SingleAnimation
{
private:
	std::vector< AnimDrawingData > singleAnim;

public:
	explicit SingleAnimation(const AnimTextureElement& animElement);
	~SingleAnimation() = default;
	SingleAnimation( const SingleAnimation& ) = delete;
	SingleAnimation& operator= ( const SingleAnimation& ) = delete;
	SingleAnimation( SingleAnimation&& ) = default;
	SingleAnimation& operator= ( SingleAnimation&& ) = default;
	
	unsigned framesNumber() const;
	unsigned getDuration(unsigned index) const;
	const AnimDrawingData& operator[](unsigned index) const;
	void drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned frameNumber);
	void drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned frameNumber);
	void drawFrameToCenter(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned frameNumber);
	void incrementCurrentFrame(CaseAnim& anim) const;
};

class AnimTexturesDrawing
{
private:
	std::vector< SingleAnimation > animations;

public:
	explicit AnimTexturesDrawing(const LoadedAnimTexturesList& loadedTextureList);
	~AnimTexturesDrawing() = default;
	AnimTexturesDrawing( const AnimTexturesDrawing& ) = delete;
	AnimTexturesDrawing& operator= ( const AnimTexturesDrawing& ) = delete;
	AnimTexturesDrawing( AnimTexturesDrawing&& ) = default;
	AnimTexturesDrawing& operator= ( AnimTexturesDrawing&& ) = default;
	
	std::size_t size() const;
	const SingleAnimation& operator[](unsigned index) const;
	SingleAnimation& operator[](unsigned index);
	void drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned animNumber, unsigned frameNumber);
	void drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned animNumber, unsigned frameNumber);
	void drawFrameToCenter(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned animNumber, unsigned frameNumber);
	bool isDataChunkValid(const CaseAnim& animChunk) const;
};

#endif //ANIM_TEXTURES_DRAWING_H