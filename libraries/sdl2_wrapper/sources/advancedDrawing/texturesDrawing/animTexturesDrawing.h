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
	
	size_t framesNumber() const;
	unsigned getDuration(size_t index) const;
	const AnimDrawingData& operator[](size_t index) const;
	void drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t frameNumber);
	void drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, std::size_t frameNumber);
	void drawFrameToCenter(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t frameNumber);
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
	const SingleAnimation& operator[](size_t index) const;
	SingleAnimation& operator[](size_t index);
	void drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t animNumber, std::size_t frameNumber);
	void drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, std::size_t animNumber, std::size_t frameNumber);
	void drawFrameToCenter(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t animNumber, std::size_t frameNumber);
	bool isDataChunkValid(const CaseAnim& animChunk) const;
};

#endif //ANIM_TEXTURES_DRAWING_H