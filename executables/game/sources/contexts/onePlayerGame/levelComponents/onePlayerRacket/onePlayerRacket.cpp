#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"

OnePlayerRacket::OnePlayerRacket(Essentials& essentials, const PlayerData& playerData):
	glueLevel{0},
	data{playerData.racketSize, playerData.racketSpeed, GameScreenHeight - SQR_SIZE - 10 * SQR_SIZE / 64},
	standardRacket{essentials.logs, essentials.rndWnd, RacketIsBlue},
	stickyRacket{essentials.logs, essentials.rndWnd, RacketIsGreen},
	frozenRacket{essentials.logs, essentials.rndWnd, FrozenBlueRacket}
{
	setRacketRect();
}

void OnePlayerRacket::setRacketRect()
{
	rect.x = data.get_x_pos() - standardRacket.getWidth(data.getSize()) / 2;
	rect.y = data.get_y_pos();
	rect.w = standardRacket.getWidth(data.getSize());
	rect.h = standardRacket.getHeight(data.getSize());
}

void OnePlayerRacket::drawRacket(sdl2::RendererWindow& rndWnd)
{
	if( false == data.isRacketFreezed() )
	{
		if( glueLevel == 0 )
		{
			standardRacket.drawRacket(rndWnd, data.getSize(), Offset{data.get_x_pos(), data.get_y_pos()});
		}
		else{
			stickyRacket.drawRacket(rndWnd, data.getSize(), Offset{data.get_x_pos(), data.get_y_pos()});
		}
	}
	else{
		frozenRacket.drawRacket(rndWnd, data.getSize(), Offset{data.get_x_pos(), data.get_y_pos() } );
	}
}
