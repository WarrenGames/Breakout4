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
	std::vector< std::vector< wxImage > > bricksTextures;
	bool isLoadingPerfect;
	
public:
	explicit OnePBricksTextures(wxTextCtrl *logWindow);
	~OnePBricksTextures() = default;
	OnePBricksTextures( const OnePBricksTextures& ) = delete;
	OnePBricksTextures& operator= ( const OnePBricksTextures& ) = delete;
	
	bool wasLoadingPerfect() const;
	void drawSingleBrick(wxDC& drawContext, const BrickData& brickData, const Offset& position) const;
	std::size_t getCategorySize(const BrickData& brickData) const;
	std::size_t getSize() const;
	
private:
	void loadAllTextures(wxTextCtrl& logWindow);
	void loadTexturesPack(const std::string& texturesEnumFilePath, std::vector< wxImage >& texturePack, wxTextCtrl& logWindow);
	void drawErrorCase(wxDC& drawContext, const Offset& position) const;
};

bool wxImageLoadedWithSuccess(const wxImage& image);

#endif //ONE_PLAYER_BRICKS_TEXTURES_H