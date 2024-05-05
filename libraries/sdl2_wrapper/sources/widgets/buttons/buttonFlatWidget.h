#ifndef H_BUTTON_FLAT
#define H_BUTTON_FLAT

#include "texturing/texturesCombo.h"
#include <string>

struct AppLogFiles;
struct Offset;
namespace sdl2{ class RendererWindow; }

class ButtonFlat
{
private:
	TextureCombo texture;
	bool clicked;
	bool hovered;

public:
	explicit ButtonFlat(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, int xpos, int ypos);
	explicit ButtonFlat(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, int xpos, int ypos, bool centered);
	~ButtonFlat() = default;
	ButtonFlat( const ButtonFlat& ) = delete;
	ButtonFlat& operator = ( const ButtonFlat& ) = delete;
	ButtonFlat( ButtonFlat&& ) = default;
	ButtonFlat& operator= ( ButtonFlat&& ) = default;

	operator bool() const;
	void updateButton(const Offset& mousePosition, bool mouseButtonState);
	void drawButton(sdl2::RendererWindow& rndWnd) const;
	bool buttonClicked() const;
	bool buttonHovered() const;
};

#endif //H_BUTTON_FLAT
