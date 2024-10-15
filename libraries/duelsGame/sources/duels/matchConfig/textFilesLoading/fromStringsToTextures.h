#ifndef FROM_STRINGS_TO_TEXTURES_H
#define FROM_STRINGS_TO_TEXTURES_H

#include <vector>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct TextureCombo;
class TextsBlocks;
struct SDL_Color;

void createZoneChoiceTextsTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, std::vector< TextureCombo >& textures, int fontSize);

#endif //FROM_STRINGS_TO_TEXTURES_H