#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/colorComponent.h"

igl::Color::Color():
	red{ 0 },
	green{ 0 },
	blue{ 0 },
	alpha{ 0 }
{

}

igl::Color::Color(unsigned red_, unsigned green_, unsigned blue_, unsigned alpha_):
	red{ red_ },
	green{ green_ },
	blue{ blue_ },
	alpha{ alpha_ }
{

}

igl::Color::Color(const SDL_Color& color):
	red{ static_cast<unsigned>( color.r ) },
	green{ static_cast<unsigned>( color.g ) },
	blue{ static_cast<unsigned>( color.b ) },
	alpha{ static_cast<unsigned>( color.a ) }
{
	
}

void igl::Color::makeSdlColor(SDL_Color& color)
{
	color.r = static_cast<Uint8>( red );
	color.g = static_cast<Uint8>( green );
	color.b = static_cast<Uint8>( blue );
	color.a = static_cast<Uint8>( alpha );
}

bool igl::Color::areComponentsValid() const
{
	return red < 256 && green < 256 && blue < 256;
}

SDL_Color igl::Color::getSDLColor() const
{
	SDL_Color color{ static_cast<Uint8>(red), static_cast<Uint8>(green), static_cast<Uint8>(blue), static_cast<Uint8>(alpha)};
	return color;
}