#ifndef BAT_FACTORY_H
#define BAT_FACTORY_H

#include "halloween/bat/badBatData.h"
#include "halloween/bat/badBatDrawer.h"

struct Essentials;

class BatObject
{
private:
	BadBatData badBatData;
	BadBatDrawer badBatDrawer;
	unsigned batStartingPoint; //Can be bat::MoveFromRight or bat::MoveFromLeft

public:
	explicit BatObject(Essentials& essentials);
	~BatObject() = default;
	BatObject( const BatObject& ) = delete;
	BatObject& operator= ( const BatObject& ) = delete;
	BatObject( BatObject&& ) = default;
	BatObject& operator= ( BatObject&& ) = default;
	
	void update();
	
	const AccurCoords& getBatPosition() const;
	int getFaceHeight() const;
	unsigned getMoveState() const;
	void drawBat(sdl2::RendererWindow& rndWnd);
	
	bool canStartActivity() const;
	void startBadBatActivity();
	
	void changeFace(std::size_t newFace);
};

#endif //BAT_FACTORY_H