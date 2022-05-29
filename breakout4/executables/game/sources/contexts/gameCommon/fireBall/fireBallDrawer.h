#ifndef GAME_COMMON_FIRE_BALL_DRAWER_H
#define GAME_COMMON_FIRE_BALL_DRAWER_H

#include "advancedDrawing/texturesLoading/2dimTexturesLoading.h"
#include "advancedDrawing/texturesDrawing/2dimTexturesDrawing.h"

struct Essentials;
struct FireBallDrawData;
class ObjectMoving;

class FireBallDrawer
{
private:
	Matrix2DTexturesLoading loadedTextures;
	Matrix2DTexturesDrawing drawer;

public:
	explicit FireBallDrawer(Essentials& essentials);
	~FireBallDrawer() = default;
	FireBallDrawer( const FireBallDrawer& ) = delete;
	FireBallDrawer& operator= ( const FireBallDrawer& ) = delete;
	FireBallDrawer( FireBallDrawer&& ) = default;
	FireBallDrawer& operator= ( FireBallDrawer&& ) = default;
	
	bool wasLoadingPerfect() const;
	void drawFireBall(Essentials& essentials, const FireBallDrawData& drawData, const ObjectMoving& move);
};

#endif //GAME_COMMON_FIRE_BALL_DRAWER_H