#ifndef INTERFACE_GENERATOR_LANGUAGE_COLOR_COMPONENT_H
#define INTERFACE_GENERATOR_LANGUAGE_COLOR_COMPONENT_H

#include "SDL_pixels.h"

namespace igl
{
	struct Color
	{
		unsigned red;
		unsigned green;
		unsigned blue;
		unsigned alpha;
		
		explicit Color();
		explicit Color(unsigned red_, unsigned green_, unsigned blue_, unsigned alpha_);
		explicit Color(const SDL_Color& color);
		~Color() = default;
		Color( const Color& ) = default;
		Color& operator= ( const Color& ) = default;
		void makeSdlColor(SDL_Color& color);
		
		bool areComponentsValid() const;
		SDL_Color getSDLColor() const;
	};
}

#endif //INTERFACE_GENERATOR_LANGUAGE_COLOR_COMPONENT_H