#ifndef ONE_PLAYER_RIMS_SCORE_VALUE_H
#define ONE_PLAYER_RIMS_SCORE_VALUE_H

#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include <vector>

struct Essentials;
class RimsScoreStock;

class RimsScoreValueDrawing
{
private:
	TextsBlocks texts;
	sdl2::Font font;
	std::vector< TextureCombo > pointsTexture;
	bool isLoadingPerfect;

public:
	explicit RimsScoreValueDrawing(Essentials& essentials, const RimsScoreStock& scoresValues);
	~RimsScoreValueDrawing() = default;
	RimsScoreValueDrawing( const RimsScoreValueDrawing& ) = delete;
	RimsScoreValueDrawing& operator= ( const RimsScoreValueDrawing& ) = delete;
	RimsScoreValueDrawing( RimsScoreValueDrawing&& ) = default;
	RimsScoreValueDrawing& operator= ( RimsScoreValueDrawing&& ) = default;
	
	void drawText(Essentials& essentials, std::size_t index) const;

private:
	void loadTextures(Essentials& essentials, const RimsScoreStock& scoresValues);
};

#endif //ONE_PLAYER_RIMS_SCORE_VALUE_H