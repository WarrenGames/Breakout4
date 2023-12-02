#ifndef ONE_PLAYER_BRICKS_TEXTURES_H
#define ONE_PLAYER_BRICKS_TEXTURES_H

#include "wx/image.h"
#include <vector>

class wxTextCtrl;
struct Offset;
struct BrickData;
class wxDC;

class OnePBricksTextures
{
private:
	bool isLoadingPerfect;
	std::vector< wxImage > generic;
	std::vector< wxImage > rich;
	wxImage bonusBrick;
	std::vector< wxImage > giftBricks;
	std::vector< wxImage > tenPtsBrick;
	std::vector< wxImage > hardBricks;
	wxImage iceCubeBrick;
	wxImage pinguinBrick;
	wxImage hellSkullBrick;
	std::vector< wxImage > lavaStoneBricks;

public:
	explicit OnePBricksTextures(wxTextCtrl *logWindow);
	~OnePBricksTextures() = default;
	OnePBricksTextures( const OnePBricksTextures& ) = delete;
	OnePBricksTextures& operator= ( const OnePBricksTextures& ) = delete;
	
	bool wasLoadingPerfect() const;
	void drawSingleBrick(wxDC& drawContext, const BrickData& brickData, const Offset& position) const;

private:
	void drawGeneric(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawRich(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawBonusCoinBrick(wxDC& drawContext, const Offset& position) const;
	void drawGiftBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawTenPtsBricks(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawSolidBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawIceBricks(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawIceCube(wxDC& drawContext, const Offset& position) const;
	void drawHellBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const;
	void drawLavaStoneBrick(wxDC& drawContext, unsigned brickIndex, const Offset& position) const;
	
	void checkRessourcesLoading(wxTextCtrl& logWindow);
	void checkGenericsBricks(wxTextCtrl& logWindow);
	void checkRichBricks(wxTextCtrl& logWindow);
	void checkBonusBrick(wxTextCtrl& logWindow);
	void checkTenPointsBrick(wxTextCtrl& logWindow);
	void checkHardBrick(wxTextCtrl& logWindow);
	void checkGiftBricks(wxTextCtrl& logWindow);
	void checkIceBricks(wxTextCtrl& logWindow);
	void checkHellSkullBrick(wxTextCtrl& logWindow);
	void checkLavaStoneBrick(wxTextCtrl& logWindow);
	
	void loadGenericBricks(wxTextCtrl& logWindow);
	void loadRichBricks(wxTextCtrl& logWindow);
	void loadGiftBricks(wxTextCtrl& logWindow);
	void load10ptsBrick(wxTextCtrl& logWindow);
	void loadHardBricks(wxTextCtrl& logWindow);
	void loadLavaStoneBrick(wxTextCtrl& logWindow);
};

bool wxImageLoadedWithSuccess(const wxImage& image);

#endif //ONE_PLAYER_BRICKS_TEXTURES_H