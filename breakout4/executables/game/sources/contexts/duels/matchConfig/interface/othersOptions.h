#ifndef DUELS_ZONECH_OTHER_OPTIONS_H
#define DUELS_ZONECH_OTHER_OPTIONS_H

#include "widgets/editBoxes/uint_editBox.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>

struct AppLogFiles;
namespace duels{

struct LevelOptions;
	
enum{ PTS_PLAY_IN_ZONE, SEC_BEF_NEW_COIN, COIN_IN_ZONE_MAX, SEC_BEF_NEW_BALL, BALL_IN_ZONE_MAX, OTH_OPT_MAX};

class OtherOptions
{
private:
	const TextsBlocks langTexts;
	std::array< TextureCombo, duels::OTH_OPT_MAX > texts;
	std::array< UintEditBox, duels::OTH_OPT_MAX > editBoxes;
	
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
	
};

}

#endif //DUELS_ZONECH_OTHER_OPTIONS_H