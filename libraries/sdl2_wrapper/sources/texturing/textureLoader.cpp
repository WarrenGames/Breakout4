#include "texturing/textureLoader.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "text/sdl2ttf_font.h"
#include "texturing/loadSDL2.h"
#include "customTypes/positionTypes.h"
#include "SDL_image.h"
#include <cassert>

sdl2::TextureLoader::TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath):
	surface{ IMG_Load( texturePath.c_str() ) }
{
	if( surface )
	{
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface", IMG_GetError() );
	}
}

sdl2::TextureLoader::TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& col, int width, int height):
	surface{ SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0) }
{
	if( surface )
	{
		SDL_FillRect( surface.get(), nullptr, SDL_MapRGBA(surface->format , col.r, col.g, col.b, col.a) );
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface", SDL_GetError() );
	}
}

sdl2::TextureLoader::TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& color):
	surface{ TTF_RenderUTF8_Blended(font.get(), text.c_str(), color) }
{
	if( surface )
	{
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface", TTF_GetError() );
	}
}

sdl2::TextureLoader::TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& txtCol, const SDL_Color& roundCol):
	surface{ TTF_RenderUTF8_Shaded(font.get(), text.c_str(), txtCol, roundCol) }
{
	if( surface )
	{
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface", TTF_GetError() );
	}
}

sdl2::TextureLoader::TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis)
{
	assert( axis == GradientTextureOnX || axis == GradientTextureOnY );
	createGradient(logs, rndWnd, rect, startColor, endColor, axis);
}

sdl2::TextureLoader::TextureLoader(sdl2::TexturePtr&& ptr)
{
	texture = std::move( ptr );
}

sdl2::TextureLoader& sdl2::TextureLoader::operator= ( sdl2::TexturePtr&& ptr)
{
	texture = std::move( ptr );
	return *this;
}

sdl2::TextureLoader::operator bool() const
{
	return texture.get() != nullptr;
}

bool sdl2::TextureLoader::wasLoadingPerfect() const
{
	return texture.get() != nullptr;
}

void sdl2::TextureLoader::loadTextureFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath)
{
	surface.reset( IMG_Load(texturePath.c_str() ) );
	if( surface )
	{
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface with SDL2_image", IMG_GetError() );
	}
}

void sdl2::TextureLoader::loadTextureSquare(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& col, int width, int height)
{
	surface.reset( SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0) );
	if( surface )
	{
		SDL_FillRect( surface.get(), nullptr, SDL_MapRGBA(surface->format , col.r, col.g, col.b, col.a) );
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface with SDL2", SDL_GetError() );
	}
}

void sdl2::TextureLoader::loadBlendedText(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& color)
{
	surface.reset( TTF_RenderUTF8_Blended(font.get(), text.c_str(), color) );
	if( surface )
	{
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface with SDL2_ttf", TTF_GetError() );
	}
}

void sdl2::TextureLoader::loadShadedText(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& txtCol, const SDL_Color& roundCol)
{
	surface.reset( TTF_RenderUTF8_Shaded(font.get(), text.c_str(), txtCol, roundCol) );
	if( surface )
	{
		createSDL_Texture(logs, rndWnd);
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface with SDL2_ttf", TTF_GetError() );
	}
}

void sdl2::TextureLoader::createSDL_Texture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	texture.reset( SDL_CreateTextureFromSurface(rndWnd.getRend(), surface.get() ) );
	if( nullptr == texture )
	{
		logs.error.wrRessourceCreationError("SDL_Texture", SDL_GetError() );
	}
	freeSurface();
}

void sdl2::TextureLoader::freeSurface()
{
	if( surface )
	{
		surface.reset();
	}
}

void sdl2::TextureLoader::freeTexture()
{
	if( texture )
	{
		texture.reset();
	}
}

void sdl2::TextureLoader::freeAllRessources()
{
	freeSurface();
	freeTexture();
}

void sdl2::TextureLoader::createGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis)
{
	if( sdl2::SurfacePtr tempSurf{ SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0) } )
	{
		switch( axis )
		{
			case GradientTextureOnX:
				drawHorizontalGradient(tempSurf, 0, rect.w, startColor, endColor);
				createTexture(logs, rndWnd, tempSurf);
				break;
			case GradientTextureOnY:
				drawVerticalGradient(tempSurf, 0, rect.h, startColor, endColor);
				createTexture(logs, rndWnd, tempSurf);
				break;
		}
	}
	else{
		logs.error << "Error: couldn't create gradient texture with " << rect.w << " pixels width and " << rect.h << " pixels height.\n";  
	}
}

void sdl2::TextureLoader::setDimensions(int& width, int& height) const
{
	if( texture )
	{
		SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	}
	else{
		width = 0;
		height = 0;
	}
}

void sdl2::TextureLoader::createTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::SurfacePtr& tempSurf)
{
	texture.reset( SDL_CreateTextureFromSurface(rndWnd.getRend(), tempSurf.get() ) );
	
	if( ! texture )
	{
		logs.error << "Error: couldn't create SDL_Texture, because: " << SDL_GetError() << " .\n";
	}
}