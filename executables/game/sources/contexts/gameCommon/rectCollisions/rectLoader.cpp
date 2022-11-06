#include "contexts/gameCommon/rectCollisions/rectLoader.h"
#include "types/essentialsStruct.h"
#include <fstream>
#include <sstream>
#include <cassert>

RectLoader::RectLoader(Essentials& essentials, std::size_t vectorSize, const std::string& rectsFile, unsigned rectId):
	rects{vectorSize},
	isLoadingPerfect{true}
{
	assert( vectorSize > 0 );
	openFileForLoading(essentials, rectsFile, rectId);
}

bool RectLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

const SDL_Rect& RectLoader::getRect(std::size_t index) const
{
	assert( index < rects.size() );
	return rects[index];
}

void RectLoader::openFileForLoading(Essentials& essentials, const std::string& rectsFile, unsigned rectId)
{
	if( std::ifstream file{ rectsFile } )
	{
		std::string fileLine;
		SDL_Rect rect{ 0, 0, 0, 0};
		unsigned id{0};
		std::size_t index{0};
		unsigned fileLineNumber{1};
		while( std::getline( file, fileLine ) )
		{
			std::istringstream lineStream{ fileLine };
			if( lineStream >> id >> index >> rect.x >> rect.y >> rect.w >> rect.h )
			{
				if( id == rectId && index < rects.size() )
				{
					rects[index] = rect;
				}
				else{
					isLoadingPerfect = false;
					essentials.logs.error.wrReadErrorMessage(rectsFile, "textures rects data", fileLineNumber);
				}
			}
			else{
				isLoadingPerfect = false;
				essentials.logs.error.wrReadErrorMessage(rectsFile, "texture rects data", fileLineNumber);
			}
			fileLineNumber++;
		}
	}
	else{
		isLoadingPerfect = false;
		essentials.logs.error.wrFileOpeningError(rectsFile, "load textures rects data");
	}
}