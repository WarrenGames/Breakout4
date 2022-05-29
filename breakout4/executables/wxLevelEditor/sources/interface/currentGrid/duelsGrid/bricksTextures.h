#ifndef DUELS_BRICKS_TEXTURES_H
#define DUELS_BRICKS_TEXTURES_H

//#include "consts/duelsGridConsts.h"
#include "wx/image.h"
#include <vector>
#include <iosfwd>

class DuelsBricksTextures
{
private:
	std::vector< wxImage > rims;
	std::vector< wxImage > toughBricks;
	std::vector< wxImage > pot;
	
public:
	explicit DuelsBricksTextures(std::ofstream& errorLog);
	~DuelsBricksTextures() = default;
	DuelsBricksTextures( const DuelsBricksTextures& ) = delete;
	DuelsBricksTextures& operator= ( const DuelsBricksTextures& ) = delete;
	
	operator bool() const;
	void drawSingleBrick(wxDC& drawContext, const BrickData& brickData, const Offset& position) const;
	
};

#endif //DUELS_BRICKS_TEXTURES_H