#ifndef PUMPKIN_DRAWER_H
#define PUMPKIN_DRAWER_H

#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"
#include "texturing/texturesCombo.h"
#include <array>

struct Essentials;
struct PumpkinCombo;

class PumpkinDrawer
{
private:
	std::array< TextureCombo, PUMPK_MAX > textures;
	bool isLoadingPerfect;

public:
	explicit PumpkinDrawer(Essentials& essentials);
	~PumpkinDrawer() = default;
	PumpkinDrawer( const PumpkinDrawer& ) = delete;
	PumpkinDrawer& operator= ( const PumpkinDrawer& ) = delete;
	PumpkinDrawer( PumpkinDrawer&& ) = default;
	PumpkinDrawer& operator= ( PumpkinDrawer&& ) = default;
	
	void drawPumpkin(Essentials& essentials, const PumpkinCombo& pumpkin);
	
	operator bool() const;
	
	int getTextureWidth(std::size_t textureIndex) const;
	int getTextureHeight(std::size_t textureIndex) const;
	
};

#endif //PUMPKIN_DRAWER_H