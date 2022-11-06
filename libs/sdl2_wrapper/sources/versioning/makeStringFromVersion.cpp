#include "versioning/makeStringFromVersion.h"
#include "SDL_version.h"

std::string sdl2::getVersionNumber(const SDL_version& version)
{
	return std::string{ std::to_string(static_cast<int>(version.major) ) + "." 
						+ std::to_string(static_cast<int>(version.minor) ) + "." 
						+ std::to_string(static_cast<int>(version.patch) ) };
}