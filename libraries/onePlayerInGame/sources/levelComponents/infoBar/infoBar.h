#ifndef P1_INFO_BAR_H
#define P1_INFO_BAR_H

#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include <vector>

struct PlayerData;
struct Essentials;
namespace sdl2{ class RendererWindow; }
class RacketData;

namespace infoBarTexts{ 
	enum{ BallsInBag, 	// = 0
		  PlayerScore, 	// = 1
		  RacketSpeed, 	// = 2
		  BonusCoinNumber, 	// = 3
		  Max }; 			// = 4
}

class InfoBar
{
private:
	bool isLoadingPerfect;
	const sdl2::Font fancyFont;
	TextureCombo brickTexture;
	std::vector< TextureCombo > barTexts;
	std::vector< TextureCombo > blackSquares;
	std::vector< bool > isGraphicalTextUpdateNeeded;
	std::vector< TextureCombo > dataTexts;

public:
	explicit InfoBar(Essentials& essentials);
	~InfoBar() = default;
	InfoBar( const InfoBar& ) = delete;
	InfoBar& operator= ( const InfoBar& ) = delete;
	InfoBar( InfoBar&& ) = default;
	InfoBar& operator= ( InfoBar&& ) = default;
	
	operator bool() const;
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void updateDataTexts(Essentials& essentials, const PlayerData& playerData, const RacketData& racketData);
	void setUpdateFlag(std::size_t index);
	void updateEverything();

private:
	void createGraphicalBarTexts(Essentials& essentials);
	void createBlackSquares(Essentials& essentials, std::size_t index, const SDL_Rect& rect, int y_center);
	bool areAllTexturesAllocated() const;
	
	void drawBricksTextures(sdl2::RendererWindow& rndWnd);
	void drawAllTexts(sdl2::RendererWindow& rndWnd) const;
	void drawAllBlackSquares(sdl2::RendererWindow& rndWnd) const;
	void drawData(sdl2::RendererWindow& rndWnd) const;
	
	void updateText(Essentials& essentials, unsigned inputValue, std::size_t index, const SDL_Color& col, const Offset& position);
	void updateText(Essentials& essentials, double inputValue, std::size_t index, const SDL_Color& col, const Offset& position);
};

#endif //P1_INFO_BAR_H