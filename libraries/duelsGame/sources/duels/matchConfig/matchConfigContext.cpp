#include "duels/matchConfig/matchConfigContext.h"
#include "types/essentialsStruct.h"
#include "duels/matchConfig/interface/zoneChoiceThings.h"
#include "duels/controls/inputConfigContext.h"
#include "duels/zones/simpleZone/simpleZoneContext.h"
#include "duels/zones/halloween/halloweenContext.h"
#include "duels/zones/metalStrings/metalStringsContext.h"
#include "duels/matchConfig/zoneSpecificOptions/halloween/halloweenSpecific.h"
#include "duels/championshipEnd/champEndContext.h"
#include "duels/matchConfig/bonusesSlots/bonusesSlotsContext.h"
#include "duels/matchConfig/zoneChoice/zoneChoiceContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void duels::matchConfig::context(Essentials& essentials, unsigned finalScore, bool& quitDuels)
{
	ZoneChoiceThings zoneChoiceThings{essentials, finalScore};
	
	while( false == quitDuels )
	{
		essentials.inp.updateEvents();
		duels::matchConfig::quitContext(quitDuels, essentials.inp);
		duels::matchConfig::update(essentials, zoneChoiceThings);
		duels::matchConfig::drawEverything(essentials, zoneChoiceThings);
		duels::matchConfig::runInputConfigurationScreen(essentials, zoneChoiceThings.inputScreenButton);
		duels::matchConfig::runChosenZone(essentials, finalScore, zoneChoiceThings);
		duels::matchConfig::zoneConfig(essentials, zoneChoiceThings);
		duels::matchConfig::zonesChoiceInterface(essentials, zoneChoiceThings);
		duels::matchConfig::bonusesConfigInterface(essentials, zoneChoiceThings);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		duels::matchConfig::stopConfigBecauseOfWinner(finalScore, zoneChoiceThings.levelOptions, quitDuels);
	}
	duels::end::context(essentials, finalScore, zoneChoiceThings.levelOptions);
}

void duels::matchConfig::quitContext(bool& quitContext, input::User& inp)
{
	if( inp.getSDL_quit() || inp.getKeyState(input::KeybOut) )
	{
		quitContext = true;
		inp.setKeyStateToFalse(input::KeybOut);
	}
}

void duels::matchConfig::update(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings)
{
	zoneChoiceThings.catchUserFocus(essentials, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	zoneChoiceThings.graphics.spin.update();
	zoneChoiceThings.inputScreenButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	zoneChoiceThings.zoneChoiceButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	zoneChoiceThings.runZoneButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	zoneChoiceThings.updateScoreGraphics(essentials);
}

void duels::matchConfig::drawEverything(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		zoneChoiceThings.drawEverything(essentials, essentials.inp.getMousePosition());
		essentials.rndWnd.displayRenderer();
	}
}

void duels::matchConfig::runInputConfigurationScreen(Essentials& essentials, const TextButton& inputScreenBtn)
{
	if( inputScreenBtn.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		duels::inputCfg::mainContext(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::matchConfig::runChosenZone(Essentials& essentials, unsigned finalScore, ZoneChoiceThings& zoneThings)
{
	if( ( zoneThings.graphics.panelsTextures.isMouseOverCurrentPanel(essentials.inp.getMousePosition(), zoneThings.selectedZone) && essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) )
		|| zoneThings.runZoneButton.buttonClicked() )
	{
		duels::matchConfig::zoneChoiceWithIndex(essentials, finalScore, zoneThings);
		zoneThings.graphics.setScoreUpdateFlag();
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::matchConfig::zoneChoiceWithIndex(Essentials& essentials, unsigned finalScore, ZoneChoiceThings& zoneThings)
{
	zoneThings.levelOptions.currentZoneEnum = zoneThings.selectedZone;
	switch( zoneThings.selectedZone )
	{
		case duels::ZoneStandard:
			zoneThings.levelOptions.avoidBadMaxValues();
			duels::simple::context(essentials, finalScore, zoneThings.levelOptions);
			break;
		case duels::ZoneHalloween:
			zoneThings.levelOptions.avoidBadMaxValues();
			duels::halloween::context(essentials, finalScore, zoneThings.levelOptions);
			break;
		case duels::ZoneStrings:
			zoneThings.levelOptions.avoidBadMaxValues();
			duels::strings::context(essentials, finalScore, zoneThings.levelOptions);
			break;
	}
}

void duels::matchConfig::zoneConfig(Essentials& essentials, ZoneChoiceThings& zoneThings)
{
	if( zoneThings.graphics.isSpinClicked(SpinZoneSpecific, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) ) )
	{
		switch( zoneThings.selectedZone )
		{
			case duels::ZoneStandard:
				
				break;
			case duels::ZoneHalloween:
				zoneSpec::halloween::mainContext(essentials, zoneThings.levelOptions.halloween);
				break;
		}
	}
}

void duels::matchConfig::zonesChoiceInterface(Essentials& essentials, ZoneChoiceThings& zoneThings)
{
	if( zoneThings.zoneChoiceButton.buttonClicked() )
	{
		duels::zoneChoice::context(essentials, zoneThings.selectedZone);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::matchConfig::bonusesConfigInterface(Essentials& essentials, ZoneChoiceThings& zoneThings)
{
	if( zoneThings.graphics.isSpinClicked(SpinBonuses, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) ) )
	{
		duels::bonuses::context(essentials, zoneThings);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::matchConfig::stopConfigBecauseOfWinner(unsigned finalScore, const duels::LevelOptions& levelOptions, bool& quitMatchConfig)
{
	levelOptions.setChampionshipEnd(finalScore, quitMatchConfig);
}