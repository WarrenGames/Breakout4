#include "contexts/onePlayerGame/bonusesShop/shopContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/bonusesShop/shopInterface.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerBonusesConsts.h"

constexpr SDL_Rect OneUpClickRect = { SQR_SIZE * 5, SQR_SIZE * 2, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect PowerBallClickRect = { SQR_SIZE * 9, SQR_SIZE * 2, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect EnlargeRimClickRect = { SQR_SIZE * 13, SQR_SIZE * 2, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect EnlargeRacketClickRect = { SQR_SIZE * 5, SQR_SIZE * 8, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect SpeedUpRacketClickRect = { SQR_SIZE * 9, SQR_SIZE * 8, SQR_SIZE * 2, SQR_SIZE * 5 };
constexpr SDL_Rect StickyRacketClickRect = { SQR_SIZE * 13, SQR_SIZE * 8, SQR_SIZE * 2, SQR_SIZE * 5 };

void onePlayerShop::context(Essentials& essentials, PlayerData& playerData)
{
	onePlayerShop::ShopInterface shopInterface{essentials, playerData};
	unsigned selection{onePlGame::BonusMax};
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
		essentials.rndWnd.clearScreen(BlackColor);
		shopInterface.drawEverything(essentials, selection);
		essentials.rndWnd.displayRenderer();
	}
}

bool onePlayerShop::isMouseOverStickyJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, StickyRacketClickRect);
}

bool onePlayerShop::isMouseOverSpeedUpJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, SpeedUpRacketClickRect);
}

bool onePlayerShop::isMouseOverEnlargeRacketJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, EnlargeRacketClickRect);
}

bool onePlayerShop::isMouseOverEnlargeRimJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, EnlargeRimClickRect);
}

bool onePlayerShop::isMouseOverPowerBallJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, PowerBallClickRect);
}

bool onePlayerShop::isMouseOverOneUpJar(const Offset& mousePosition)
{
	return isPointInRect(mousePosition, OneUpClickRect);
}

bool onePlayerShop::isPointInRect(const Offset& mousePosition, const SDL_Rect& rect)
{
	return mousePosition.x >= rect.x && mousePosition.x < rect.x + rect.w && mousePosition.y >= rect.y && mousePosition.y < rect.y + rect.h;
}

void onePlayerShop::setMouseSelection(unsigned& selection, const Offset& mousePosition)
{
	if( isMouseOverStickyJar(mousePosition) )
	{
		selection = onePlGame::BonusStickyRacket;
	}
	else if( isMouseOverSpeedUpJar(mousePosition) )
	{
		selection = onePlGame::BonusRacketSpeedUp;
	}
	else if( isMouseOverEnlargeRacketJar(mousePosition) )
	{
		selection = onePlGame::BonusEnlargeRacket;
	}
	else if( isMouseOverEnlargeRimJar(mousePosition) )
	{
		selection = onePlGame::BonusEnlargeRim;
	}
	else if( isMouseOverPowerBallJar(mousePosition) )
	{
		selection = onePlGame::BonusPowerBall;
	}
	else if( isMouseOverOneUpJar(mousePosition) )
	{
		selection = onePlGame::BonusOneMoreBallLive;
	}	
	else{
		selection = onePlGame::BonusMax;
	}
}

void onePlayerShop::quitShop(Essentials& essentials, bool& quitShop)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitShop = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
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
	if( selection < onePlGame::BonusMax && essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) )
	{
		playerData.buyABonusIfPossible(selection);
		shopInterface.bonusesCount.setUpdateFlag(selection);
		shopInterface.updateCoinNumberText(essentials, playerData);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}