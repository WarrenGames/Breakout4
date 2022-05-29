#include "contexts/onePlayerGame/bonusesShop/shopContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/bonusesShop/shopInterface.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerBonusesConsts.h"

constexpr SDL_Rect ONE_UP_RECT = { SQR_SIZE * 5, SQR_SIZE * 2, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect POWER_BALL_RECT = { SQR_SIZE * 9, SQR_SIZE * 2, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect ENLARGE_RIM_RECT = { SQR_SIZE * 13, SQR_SIZE * 2, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect ENLARGE_RACKET_RECT = { SQR_SIZE * 5, SQR_SIZE * 8, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect SPEED_UP_RACKET_RECT = { SQR_SIZE * 9, SQR_SIZE * 8, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect STICKY_RECT = { SQR_SIZE * 13, SQR_SIZE * 8, SQR_SIZE * 2, SQR_SIZE * 5 };

void onePlayerShop::context(Essentials& essentials, PlayerData& playerData)
{
	onePlayerShop::ShopInterface shopInterface{essentials, playerData};
	unsigned selection{onePlGame::BONUS_MAX};
	bool quitShop{false};
	
	while( false == quitShop )
	{
		essentials.inp.updateEvents();
		shopInterface.update();
		onePlayerShop::actAccordinglyToEvent(essentials, shopInterface, playerData, selection, quitShop);
		onePlayerShop::drawEverything(essentials, shopInterface, selection);
	}
}

void onePlayerShop::drawEverything(Essentials& essentials, onePlayerShop::ShopInterface& shopInterface, unsigned selection)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BLACK_COL);
		shopInterface.drawEverything(essentials, selection);
		essentials.rndWnd.displayRenderer();
	}
}

bool onePlayerShop::isMouseOverStickyJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, STICKY_RECT);
}

bool onePlayerShop::isMouseOverSpeedUpJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, SPEED_UP_RACKET_RECT);
}

bool onePlayerShop::isMouseOverEnlargeRacketJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, ENLARGE_RACKET_RECT);
}

bool onePlayerShop::isMouseOverEnlargeRimJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, ENLARGE_RIM_RECT);
}

bool onePlayerShop::isMouseOverPowerBallJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, POWER_BALL_RECT);
}

bool onePlayerShop::isMouseOverOneUpJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, ONE_UP_RECT);
}

bool onePlayerShop::isPointInRect(const Offset& mousePosition, const SDL_Rect& rect)
{
	return mousePosition.x >= rect.x && mousePosition.x < rect.x + rect.w && mousePosition.y >= rect.y && mousePosition.y < rect.y + rect.h;
}

void onePlayerShop::setMouseSelection(unsigned& selection, const Offset& mousePosition)
{
	if( isMouseOverStickyJar(mousePosition) )
	{
		selection = onePlGame::BONUS_STICKY;
	}
	else if( isMouseOverSpeedUpJar(mousePosition) )
	{
		selection = onePlGame::BONUS_RACKET_SPEEDUP;
	}
	else if( isMouseOverEnlargeRacketJar(mousePosition) )
	{
		selection = onePlGame::BONUS_ENLARGE_RACKET;
	}
	else if( isMouseOverEnlargeRimJar(mousePosition) )
	{
		selection = onePlGame::BONUS_ENLARGE_RIM;
	}
	else if( isMouseOverPowerBallJar(mousePosition) )
	{
		selection = onePlGame::BONUS_POWERBALL;
	}
	else if( isMouseOverOneUpJar(mousePosition) )
	{
		selection = onePlGame::BONUS_ONE_UP;
	}	
	else{
		selection = onePlGame::BONUS_MAX;
	}
}

void onePlayerShop::quitShop(Essentials& essentials, bool& quitShop)
{
	if( essentials.inp.getKeyState(input::KEYB_OUT) || essentials.inp.getSDL_quit() )
	{
		quitShop = true;
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
	}
}

void onePlayerShop::actAccordinglyToEvent(Essentials& essentials, onePlayerShop::ShopInterface& shopInterface, PlayerData& playerData, unsigned& selection, bool& quitShop)
{
	onePlayerShop::setMouseSelection(selection, essentials.inp.getMousePosition());
	onePlayerShop::quitShop(essentials, quitShop);
	onePlayerShop::buyABonus(essentials, shopInterface, playerData, selection);
	shopInterface.bonusesCount.updateNeededTexts(essentials, playerData, shopInterface.bagIcons);
}

void onePlayerShop::buyABonus(Essentials& essentials, onePlayerShop::ShopInterface& shopInterface, PlayerData& playerData, unsigned& selection)
{
	if( selection < onePlGame::BONUS_MAX && essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) )
	{
		playerData.buyABonusIfPossible(selection);
		shopInterface.bonusesCount.setUpdateFlag(selection);
		shopInterface.updateCoinNumberText(essentials, playerData);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}