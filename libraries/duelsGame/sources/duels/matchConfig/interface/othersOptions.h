#ifndef DUELS_ZONECH_OTHER_OPTIONS_H
#define DUELS_ZONECH_OTHER_OPTIONS_H

#include "widgets/editBoxes/uint_editBox.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"
#include "consts/duelsConstexpr.h"
#include <vector>

struct AppLogFiles;
namespace duels{

struct LevelOptions;
	
enum{ PointsPlayInZone, SecondsBeforeNewCoin, MaxCoinInZone, SecondsBeforeNewBall, MaxBallInZone, OtherOptionsMax};

class OtherOptions
{
private:
	TextsBlocks langTexts;
	std::vector< TextureCombo > texts;
	std::vector< UintEditBox > editBoxes;
	
public:
	explicit OtherOptions(AppLogFiles& logs, const std::string& chosenLanguage, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, duels::LevelOptions& levelOptions);
	~OtherOptions() = default;
	OtherOptions( const OtherOptions& ) = delete;
	OtherOptions& operator= ( const OtherOptions& ) = delete;
	OtherOptions( OtherOptions&& ) = default;
	OtherOptions& operator= ( OtherOptions&& ) = default;
	
	void catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton);
	void drawEverything(sdl2::RendererWindow& rndWnd) const;
	
private:
	void drawBoxes(sdl2::RendererWindow& rndWnd) const;
	void drawTexts(sdl2::RendererWindow& rndWnd) const;
	
	void createTextsData(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont);
	void createEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, duels::LevelOptions& levelOptions);
};

}

#endif //DUELS_ZONECH_OTHER_OPTIONS_H