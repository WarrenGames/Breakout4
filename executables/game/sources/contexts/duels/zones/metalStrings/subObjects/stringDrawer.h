#ifndef DUELS_ZONE_STRING_DRAWER_H
#define DUELS_ZONE_STRING_DRAWER_H

#include "texturing/texturesCombo.h"
#include "contexts/duels/zones/metalStrings/subObjects/metalStringsData.h"
#include "time/accurateTime.h"
#include "contexts/duels/zones/metalStrings/subObjects/consts.h"
#include <vector>
#include <string>

constexpr char DuelsDataFilePath[] = "data/levels/duels/metalStringsSqr0.lvl";

struct Essentials;

namespace metalStrings{

class StringsDrawer
{
private:
	std::vector< std::vector< metalStrings::StringData > > data;
	std::vector< std::vector< TextureCombo > > textures;
	AccurateTimeDelay animDelay;

public:
	explicit StringsDrawer(Essentials& essentials, const std::string& filePath);
	~StringsDrawer() = default;
	StringsDrawer( const StringsDrawer& ) = delete;
	StringsDrawer& operator= ( const StringsDrawer& ) = delete;
	StringsDrawer( StringsDrawer&& ) = default;
	StringsDrawer& operator= ( StringsDrawer&& ) = default;
	
	operator bool () const;
	void drawAllStrings(Essentials& essentials);
	void updateAnimation();
	void setBarrierActivity(std::size_t playerNumber, unsigned directionType);
	
private:
	void drawString(Essentials& essentials, const metalStrings::StringData& stringData);
	void readDataLevelFile(Essentials& essentials, const std::string& filePath);
	void readLine(Essentials& essentials, std::istringstream& lineStream, std::size_t fileLineNumber, const std::string& filePath);
	void loadStringsTextures(Essentials& essentials, std::size_t orientation, const std::string& texturePrefix);
};

}

#endif //DUELS_ZONE_STRING_DRAWER_H