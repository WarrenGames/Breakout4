#ifndef ONE_PLAYER_BRICKS_TEXTURES_H
#define ONE_PLAYER_BRICKS_TEXTURES_H

#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include <vector>

struct BricksTexturesLoader;
struct BrickData;
namespace sdl2{ class RendererWindow; }

class OnePBricksTextures
{
private:
	std::vector< ConstAnimDraw > sprites;

public:
	explicit OnePBricksTextures(const BricksTexturesLoader& texturesLoader);
	~OnePBricksTextures() = default;
	OnePBricksTextures( const OnePBricksTextures& ) = delete;
	OnePBricksTextures& operator= ( const OnePBricksTextures& ) = delete;
	OnePBricksTextures( OnePBricksTextures&& ) = default;
	OnePBricksTextures& operator= ( OnePBricksTextures&& ) = default;

	void linkSpritesToLoadedTextures(const BricksTexturesLoader& texturesLoader);
	void drawSingleBrick(sdl2::RendererWindow& rndWnd, const BrickData& brickData, const Offset& position);
};

#endif //ONE_PLAYER_BRICKS_TEXTURES_H