#include "texturing/texturePosition.h"

TexturePosition::TexturePosition():
	position{ 0, 0 },
	on_x_centered{false},
	on_y_centered{false}
{
	
}

TexturePosition::TexturePosition(int xpos, int ypos):
	position{ xpos, ypos},
	on_x_centered{false},
	on_y_centered{false}
{
	
}

TexturePosition::TexturePosition(int xpos, int ypos, bool x_centered, bool y_centered):
	position{xpos, ypos},
	on_x_centered{x_centered},
	on_y_centered{y_centered}
{
	
}


TexturePosition::TexturePosition(const Offset& newPosition):
	position{newPosition},
	on_x_centered{false},
	on_y_centered{false}
{
	
}

TexturePosition::TexturePosition(const Offset& newPosition, bool x_centered, bool y_centered):
	position{newPosition},
	on_x_centered{x_centered},
	on_y_centered{y_centered}
{
	
}

TexturePosition::TexturePosition(const Offset& newPosition, bool bothCentered):
	position{newPosition},
	on_x_centered{bothCentered},
	on_y_centered{bothCentered}
{

}

void TexturePosition::placeOnX(int xpos)
{
	position.x = xpos;
}

void TexturePosition::placeOnY(int ypos)
{
	position.y = ypos;
}