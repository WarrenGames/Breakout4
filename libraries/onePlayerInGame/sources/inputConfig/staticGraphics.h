#ifndef ONEPL_INP_CFG_STATIC_GRAPHICS_H
#define ONEPL_INP_CFG_STATIC_GRAPHICS_H

#include "texturing/texturesCombo.h"
#include "texturing/verticalGradientTexture.h"
#include "consts/onePlayerLevelConsts.h"
#include <vector>

struct Essentials;
namespace sdl2{ class Font; }
class TextsBlocks;

namespace onePlGame{

enum{ PushNewKey, PushNewButton };
	
struct StaticGraphics
{
	const TextureCombo screenBackground;
	std::vector< TextureCombo > alwaysDrawnTextures;
	std::vector< TextureCombo > askInputTextures;
	
	explicit StaticGraphics(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& languageTexts);
	~StaticGraphics() = default;
	StaticGraphics( const StaticGraphics& ) = delete;
	StaticGraphics& operator= ( const StaticGraphics& ) = delete;
	StaticGraphics( StaticGraphics&& ) = default;
	StaticGraphics& operator= ( StaticGraphics&& ) = default;
	
	operator bool() const;
	
	void drawEverything(Essentials& essentials) const;
	void drawAllDescription(Essentials& essentials) const;
	void drawInputArrayLines(Essentials& essentials) const;
};

}

#endif //ONEPL_INP_CFG_STATIC_GRAPHICS_H