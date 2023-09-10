#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_LVL_SELECTION_BUTTONS_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_LVL_SELECTION_BUTTONS_H

#include "widgets/buttons/textButtonWidget.h"
#include "text/sdl2ttf_font.h"
#include "consts/sdlColors.h"
#include <vector>

struct Essentials;
class LevelsInfos;

namespace onePlGame{

namespace demoRecording{

constexpr std::size_t LevelsPerPage = 14;
	
class LevelsButtons
{
private:
	std::size_t currentPageNumber;
	const sdl2::Font arial;
	std::vector< std::vector< TextButton > > buttons;

public:
	explicit LevelsButtons(Essentials& essentials);
	~LevelsButtons() = default;
	LevelsButtons( const LevelsButtons& ) = delete;
	LevelsButtons& operator= ( const LevelsButtons& ) = delete;
	LevelsButtons( LevelsButtons&& ) = default;
	LevelsButtons& operator= ( LevelsButtons&& ) = default;
	
	void createButtons(Essentials& essentials, const LevelsInfos& levelsInfos);
	void nextPageIfAny();
	void previousPageIfAny();
	void updateButtons(Essentials& essentials);
	void drawCurrentPage(Essentials& essentials) const;
	bool isButtonClicked(std::size_t buttonNum) const;
};

}

}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_LVL_SELECTION_BUTTONS_H