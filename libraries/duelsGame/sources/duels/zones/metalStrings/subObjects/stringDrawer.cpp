#include "duels/zones/metalStrings/subObjects/stringDrawer.h"
#include "types/essentialsStruct.h"
#include "consts/duelsConstexpr.h"
#include <sstream>
#include <cassert>
#include <fstream>
#include <algorithm>

constexpr char HorizontalTexturePrefix[] = "textures/gameZones/factory/horizontal_string/str_h_";
constexpr char VerticalTexturePrefix[] = "textures/gameZones/factory/vertical_string/str_v_";

metalStrings::StringsDrawer::StringsDrawer(Essentials& essentials, const std::string& filePath):
	data( duels::PlayerMax ),
	textures( metalStrings::OrientationMax )
{
	readDataLevelFile(essentials, filePath);
	loadStringsTextures(essentials, metalStrings::OrientationHorizontal, HorizontalTexturePrefix);
	loadStringsTextures(essentials, metalStrings::OrientationVertical, VerticalTexturePrefix);
}

metalStrings::StringsDrawer::operator bool() const
{
	return std::all_of(textures.cbegin(), textures.cend(), [](auto &texArray){
				return std::all_of(texArray.cbegin(), texArray.cend(),[](auto &tex){ return tex.texture.wasLoadingPerfect();} ); } );
}

void metalStrings::StringsDrawer::drawAllStrings(Essentials& essentials)
{
	for( std::size_t player{0} ; player < data.size() ; ++player )
	{
		std::for_each(data[player].begin(), data[player].end(), [&essentials, this](auto str){ drawString(essentials, str); } );
	}
}

void metalStrings::StringsDrawer::updateAnimation()
{
	if( animDelay.hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		for( auto &player : data )
		{
			for( auto &string : player )
			{
				string.updateAnimation();
			}
		}
		animDelay.joinTimePoints();
	}
}

void metalStrings::StringsDrawer::setBarrierActivity(std::size_t playerNumber, unsigned directionType)
{
	assert( playerNumber < duels::PlayerMax );
	assert( directionType <= metalStrings::DirectionStop );
	for( auto &string : data[playerNumber] )
	{
		string.startDirection(directionType);
	}
}

void metalStrings::StringsDrawer::drawString(Essentials& essentials, const metalStrings::StringData& stringData)
{
	assert( stringData.orientation < metalStrings::OrientationMax );
	assert( stringData.textureIndex < metalStrings::StringsFramesNumber );
	
	switch( stringData.orientation )
	{
		case metalStrings::OrientationHorizontal:
			textures[stringData.orientation][stringData.textureIndex].draw(essentials.rndWnd, SQR_SIZE * stringData.texturePosition.x, SQR_SIZE * stringData.texturePosition.y + SQR_SIZE/4);
			break;
		case metalStrings::OrientationVertical:
			textures[stringData.orientation][stringData.textureIndex].draw(essentials.rndWnd, SQR_SIZE * stringData.texturePosition.x + SQR_SIZE/4, SQR_SIZE * stringData.texturePosition.y);
			break;
	}
}

void metalStrings::StringsDrawer::readDataLevelFile(Essentials& essentials, const std::string& filePath)
{
	if( std::ifstream dataFile{filePath} )
	{
		std::string fileLine;
		std::size_t fileLineNumber{1};
		while( std::getline(dataFile, fileLine) )
		{
			std::istringstream lineStream{fileLine};
			readLine(essentials, lineStream, fileLineNumber, filePath);
			++fileLineNumber;
		}
	}
	else{
		essentials.logs.error << "Error: failed to read '" << filePath << "' data file for the metal strings level.\n";
	}
}

void metalStrings::StringsDrawer::readLine(Essentials& essentials, std::istringstream& lineStream, std::size_t fileLineNumber, const std::string& filePath)
{
	unsigned player{0};
	Offset squarePosition{0, 0};
	unsigned orientation{metalStrings::OrientationMax};
	unsigned forwardDir{metalStrings::DirectionStop};
	unsigned backwardDir{metalStrings::DirectionStop};
	if( lineStream >> player >> squarePosition.x >> squarePosition.y >> orientation >> forwardDir >> backwardDir )
	{
		if( player < data.size() )
		{
			data[player].emplace_back( metalStrings::StringData{squarePosition, orientation, forwardDir, backwardDir} );
		}
	}
	else{
		essentials.logs.error << "Error: couldn't read all of the line number " << fileLineNumber << " in file " << filePath << ".\n"; 
	}
}

void metalStrings::StringsDrawer::loadStringsTextures(Essentials& essentials, std::size_t orientation, const std::string& texturePrefix)
{
	assert( orientation < textures.size() );
	for( std::size_t i{0} ; i < metalStrings::StringsFramesNumber ; ++i )
	{
		textures[orientation].emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, texturePrefix + std::to_string(i) + ".png"} );
	}
}

