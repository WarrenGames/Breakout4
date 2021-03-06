#include "contexts/gameCommon/halloween/bat/batFactory.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "contexts/gameCommon/halloween/bat/batConsts.h"

BatObject::BatObject(Essentials& essentials):
	badBatData{},
	badBatDrawer{essentials.logs, essentials.rndWnd},
	batStartingPoint{bat::MOVE_FROM_LEFT}
{
	
}

void BatObject::update()
{
	badBatData.update();
}

const AccurCoords& BatObject::getBatPosition() const
{
	return badBatData.getBatPosition();
}

int BatObject::getFaceHeight() const
{
	return badBatDrawer.getFaceHeight(badBatData);
}

unsigned BatObject::getMoveState() const
{
	return badBatData.getMoveState();
}

void BatObject::drawBat(sdl2::RendererWindow& rndWnd)
{
	badBatDrawer.drawBat(rndWnd, badBatData);
}

bool BatObject::canStartActivity() const
{
	return badBatData.getMoveState() == bat::MOVE_OFF;
}

void BatObject::startBadBatActivity()
{
	badBatData.startBadBatActivity();
}

void BatObject::changeFace(std::size_t newFace)
{
	badBatData.changeFace(newFace);
}