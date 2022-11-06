#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/stalactites/stalactitesConsts.h"
#include "contexts/gameCommon/pinguins/pinguinConsts.h"

AntarcticPackage::AntarcticPackage(Essentials& essentials, const PlayerData& playerData):
	stalactitesDrawer{essentials},
	stalactitesRects{essentials, stalactites::DirectionsNumber, stalactites::RectsFilePath, stalactites::RectId},
	stalactitesData{essentials, playerData},
	pinguinTextures{ essentials.logs, essentials.rndWnd, Coord2D{ pinguin::AnimFramesNumber, pinguin::DirectionsNumber}, pinguin::TexturesListFile },
	pinguinSprites{pinguinTextures},
	pinguinsData{essentials, playerData}
{
	
}

AntarcticPackage::operator bool() const
{
	return stalactitesDrawer.wasLoadingPerfect() 
		&& stalactitesRects.wasLoadingPerfect() 
		&& stalactitesData.wasLoadingPerfect()
		&& pinguinTextures.wasLoadingPerfect()
		&& pinguinsData.wasLoadingPerfect();
}

void AntarcticPackage::drawStalactites(Essentials& essentials)
{
	for( auto const &stal : stalactitesData )
	{
		if( stalactites::StateOut != stal.commonData.getState() )
			stalactitesDrawer.drawStalactite(essentials, stal.commonData);
	}
}

void AntarcticPackage::drawPinguins(Essentials& essentials)
{
	if( pinguinsData.size() > 0 )
	{
		for( auto const &ping : pinguinsData )
		{
			pinguinSprites.draw(essentials.rndWnd, Coord2D{ping.getDrawingData().frameNumber, ping.getDrawingData().direction}, 
						ping.getDrawingData().move.get_x_position(),
						ping.getDrawingData().move.get_y_position() );
		}
	}
}