#ifndef SDL2_RENDERER_WINDOW_H
#define SDL2_RENDERER_WINDOW_H

#include "customTypes/positionTypes.h"
#include "wrappers/sdl2_ptr.h"
#include <string>

class LogFile;

namespace sdl2{

class RendererWindow
{
private:
	sdl2::WindowPtr window;
	sdl2::RendererPtr renderer;
	int windowWidth;
	int windowHeight;
	bool isInitPerfect;
	
public:
	explicit RendererWindow(LogFile& log, int screenWidth, int screenHeight, const std::string& windowTitle, const std::string& iconPath);
	RendererWindow( const RendererWindow& ) = delete;
	RendererWindow& operator= ( const RendererWindow& ) = delete;
	RendererWindow( RendererWindow&& ) = default;
	RendererWindow& operator= ( RendererWindow&& ) = default;
	~RendererWindow() = default;
	
	operator bool() const;
	bool wasInitializationPerfect() const;
	void changeScreenDefinition(int newWidth, int newHeight);
	void setWindowFullScreen(bool isFullScreen);
	void centerWindow();
	void setRenderDrawBlendMode(SDL_BlendMode blendMode);
	void setWindowTitle(const std::string& windowTitle);
	void setWindowIcon(LogFile& log, const std::string& iconPath);
	int width() const;
	int height() const;
	SDL_Renderer* getRend() const;
	
	void displayRenderer();
	void setDrawColor(const SDL_Color& drawColor);
	void clearScreen(const SDL_Color& clearColor);
	void drawLine(const Offset& point1, const Offset& point2, const SDL_Color& lineColor);
	void fillRect(const SDL_Color& fillColor, const SDL_Rect& rect);
	void drawRect(const SDL_Color& rectColor, const SDL_Rect& rect);
};

}

#endif //SDL2_RENDERER_WINDOW_H