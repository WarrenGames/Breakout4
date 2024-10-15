#ifndef ONE_PLAYER_TRACE_CROSS_H
#define ONE_PLAYER_TRACE_CROSS_H

#include "texturing/texturesCombo.h"
#include "customTypes/positionTypes.h"
#include "time/accurateTime.h"
#include "consts/constexprScreen.h"

struct Essentials;

constexpr int TraceCrossOffset = SQR_SIZE / 4;

struct TraceCross
{
	Offset position;
	TextureCombo crossTexture;
	AccurateTimeDelay moveDelay;
	
	explicit TraceCross(Essentials& essentials);
	~TraceCross() = default;
	TraceCross( const TraceCross& ) = delete;
	TraceCross& operator= ( const TraceCross& ) = delete;
	TraceCross( TraceCross&& ) = default;
	TraceCross& operator= ( TraceCross&& ) = default;
	
	operator bool() const;
	
	void drawCross(Essentials& essentials, bool isMainBallActive);
};

#endif //ONE_PLAYER_TRACE_CROSS_H