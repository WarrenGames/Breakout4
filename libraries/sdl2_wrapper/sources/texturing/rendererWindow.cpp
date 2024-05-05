#include "texturing/rendererWindow.h"
#include "logging/logFile.h"
#include "SDL_image.h"

sdl2::RendererWindow::RendererWindow(LogFile& log, int screenWidth, int screenHeight, const std::string& windowTitle, const std::string& iconPath):
	window{ SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0) },
	renderer{ nullptr },
	windowWidth{0},
	windowHeight{0},
	isInitPerfect{true}
{
	if( window )
	{
		setWindowIcon(log, iconPath);
		renderer.reset( SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED) );
		
		if( renderer )
		{
			SDL_GetWindowSize(window.get(), &windowWidth, &windowHeight);
		}
		else{
			log.wrRessourceInitError("SDL_Render", SDL_GetError() );
			isInitPerfect = false;
		}
	}
	else{
		log.wrRessourceInitError("SDL_Window", SDL_GetError() );
		isInitPerfect = false;
	}
}

sdl2::RendererWindow::operator bool() const
{
	return isInitPerfect;
}

bool sdl2::RendererWindow::wasInitializationPerfect() const
{
	return isInitPerfect;
}

void sdl2::RendererWindow::changeScreenDefinition(int newWidth, int newHeight)
{
	SDL_SetWindowSize(window.get(), newWidth, newHeight);
	
	if( SDL_RenderSetLogicalSize(renderer.get(), newWidth, newHeight) == 0 )
	{
		windowWidth = newWidth;
		windowHeight = newHeight;
	}
}

void sdl2::RendererWindow::setWindowFullScreen(bool isFullScreen)
{
	if( isFullScreen )
	{
		SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else{
		SDL_SetWindowFullscreen(window.get(), 0);
	}
}

void sdl2::RendererWindow::centerWindow()
{
	SDL_SetWindowPosition(window.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void sdl2::RendererWindow::setRenderDrawBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetRenderDrawBlendMode(renderer.get(), blendMode);
}

void sdl2::RendererWindow::setWindowTitle(const std::string& windowTitle)
{
	SDL_SetWindowTitle(window.get(), windowTitle.c_str());
}

void sdl2::RendererWindow::setWindowIcon(LogFile& log, const std::string& iconPath)
{
	if( false == iconPath.empty() )
	{
		sdl2::SurfacePtr iconSurface{ IMG_Load( iconPath.c_str() ) };
	
		if( iconSurface && window )
		{
			SDL_SetWindowIcon(window.get(), iconSurface.get() );
		}
		else{
			log.wrRessourceInitError("Window icon", SDL_GetError() );
			isInitPerfect = false;
		}
	}
}

int sdl2::RendererWindow::width() const
{
	return windowWidth;
}

int sdl2::RendererWindow::height() const
{
	return windowHeight;
}

SDL_Renderer* sdl2::RendererWindow::getRend() const
{
	return renderer.get();
}

void sdl2::RendererWindow::displayRenderer()
{
	SDL_RenderPresent(renderer.get());
}

void sdl2::RendererWindow::setDrawColor(const SDL_Color& drawColor)
{
	SDL_SetRenderDrawColor(renderer.get(), drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}

void sdl2::RendererWindow::clearScreen(const SDL_Color& clearColor)
{
	setDrawColor(clearColor);
	SDL_RenderClear(renderer.get());
}

void sdl2::RendererWindow::drawLine(const Offset& point1, const Offset& point2, const SDL_Color& lineColor)
{
	setDrawColor(lineColor);
	SDL_RenderDrawLine(renderer.get(), point1.x, point1.y, point2.x, point2.y);
}

void sdl2::RendererWindow::fillRect(const SDL_Color& fillColor, const SDL_Rect& rect)
{
	setDrawColor(fillColor);
	SDL_RenderFillRect(renderer.get(), &rect);
}

void sdl2::RendererWindow::drawRect(const SDL_Color& rectColor, const SDL_Rect& rect)
{
	setDrawColor(rectColor);
	SDL_RenderDrawRect(renderer.get(), &rect);
}