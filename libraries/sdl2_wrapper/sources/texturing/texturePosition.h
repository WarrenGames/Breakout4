#ifndef SDL2_TEXTURE_POSITION_H
#define SDL2_TEXTURE_POSITION_H

#include "customTypes/positionTypes.h"

struct TexturePosition
{
	Offset position;
	bool on_x_centered;
	bool on_y_centered;
	
	explicit TexturePosition();
	explicit TexturePosition(int xpos, int ypos);
	explicit TexturePosition(int xpos, int ypos, bool x_centered, bool y_centered);
	explicit TexturePosition(const Offset& newPosition);
	explicit TexturePosition(const Offset& newPosition, bool x_centered, bool y_centered);
	explicit TexturePosition(const Offset& newPosition, bool bothCentered);
	TexturePosition( const TexturePosition& ) = default;
	TexturePosition& operator= ( const TexturePosition& ) = default;
	TexturePosition( TexturePosition&& ) = default;
	TexturePosition& operator= ( TexturePosition&& ) = default;
	
	void placeOnX(int xpos);
	void placeOnY(int ypos);
	
};

#endif //SDL2_TEXTURE_POSITION_H