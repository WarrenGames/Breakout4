#ifndef DUELS_PLAYER_SCORE_DRAWING_H
#define DUELS_PLAYER_SCORE_DRAWING_H

#include "customTypes/positionTypes.h"
#include "texturing/texturesCombo.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
struct Offset;

namespace duels{

class ScoreDraw
{
private:
	Offset offset;
	bool mustUpdate;
	TextureCombo backgroundSquare;
	TextureCombo scoreText;

public:
	explicit ScoreDraw(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, const Offset& centerDrawPosition, int playerScore);
	~ScoreDraw() = default;
	ScoreDraw( const ScoreDraw& ) = delete;
	ScoreDraw& operator= ( const ScoreDraw& ) = delete;
	ScoreDraw( ScoreDraw&& ) = default;
	ScoreDraw& operator= ( ScoreDraw&& ) = default;
	
	void updateIfPossible(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, int playerScore);
	void setUpdateFlag();
	void drawScore(sdl2::RendererWindow& rndWnd) const;
};

}

#endif //DUELS_PLAYER_SCORE_DRAWING_H