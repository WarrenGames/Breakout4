#ifndef ONEP_INPUT_THINGS_H
#define ONEP_INPUT_THINGS_H

#include "levelComponents/inputs/customInputsData.h"
#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "widgets/buttons/highlightButtonWidget.h"
#include "texturing/verticalGradientTexture.h"
#include "inputConfig/staticGraphics.h"
#include "widgets/editBoxes/boxesIncludes.h"
#include "time/accurateTime.h"
#include <string>
#include <vector>

struct Essentials;

namespace onePlGame{

struct InputThings
{
	bool isLoadingPerfect;
	CustomInputData inputData;
	AccurateTimeDelay drawDelay;
	const TextsBlocks languageTexts;
	const sdl2::Font fancyFont;
	std::vector< HighLightButton > keycodesInputsTexts;
	std::vector< HighLightButton > joystickInputsTexts;
	std::vector< HighLightButton > moveCross;
	TextureCombo joystickName;
	const onePlGame::StaticGraphics staticGraphics;
	SintEditBox axisThresholdBox;
	HighLightButton joystickMenu;
	
	explicit InputThings(Essentials& essentials);
	InputThings( const InputThings& ) = delete;
	InputThings& operator= ( const InputThings& ) = delete;
	InputThings( InputThings&& ) = default;
	InputThings& operator= ( InputThings&& ) = default;
	
	operator bool() const;
	
	void createKeycodesInputsButtons(Essentials& essentials);
	void createJoystickInputButtons(Essentials& essentials);
	void createMoveCrossButtons(Essentials& essentials);
	void createJoystickGraphicalStatus(Essentials& essentials);
	
	void drawKeycodesButtons(Essentials& essentials) const;
	void drawJoystickButtons(Essentials& essentials) const;
	void drawJoystickCrossButtons(Essentials& essentials) const;
	void drawEverything(Essentials& essentials) const;
	
	void updateEverything(Essentials& essentials);
	
	void updateKeycodesButtons(Essentials& essentials);
	void updateJoystickButtons(Essentials& essentials);
	void updateJoystickCrossButtons(Essentials& essentials);
	
	void changeKeycodesButtonsString(Essentials& essentials);
	void changeJoystickButtonsStrings(Essentials& essentials);
	void changeJoystickMoveStrings(Essentials& essentials);
	void tweakJoyAxesAndHatsNum();
	void tweakJoyAxes();
	void tweakJoyHats();
	void tweakJoyMovError();
	void readJoyBtnHighlightBtn(Essentials& essentials, HighLightButton& highlightButton, std::size_t buttonIndex);
	
	void waitForKeycodeToBePushed(Essentials& essentials, HighLightButton& highlightButton, std::size_t keycodeIndex);
	void waitForJoyBtnToBePushed(Essentials& essentials, HighLightButton& highlightButton, std::size_t buttonIndex);
	
	void changeCrossMoveStrings(Essentials& essentials);
	void tweakCrossMoveNums(unsigned& crossMoveNum);
	void tweakCrossMoveAxes(unsigned& crossMoveNum);
	void tweakCrossMoveHats(unsigned& crossMoveNum);
	void tweakCrossMoveError();
	
	std::string getKeycodeString(std::size_t arrayIndex);

	std::string getJoystickMoveString();
	std::string getJoystickBtnString(std::size_t buttonIndex);
	std::string getJoystickCrossMoveString(std::size_t moveAxis);
	
	void writeDataToConfigFiles(Essentials& essentials);
};

}

#endif //ONEP_INPUT_THINGS_H