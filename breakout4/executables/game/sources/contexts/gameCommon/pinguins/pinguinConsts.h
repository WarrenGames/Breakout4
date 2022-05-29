#ifndef GAME_PINGUIN_CONSTS_H
#define GAME_PINGUIN_CONSTS_H

namespace pinguin{

constexpr char TEXTURES_LIST_FILE[] = "data/textures/pinguinTexturesList.txt";

constexpr std::size_t TEXTURE_DIRECTIONS_NUMBER = 8;
constexpr std::size_t ANIM_FRAMES_NUMBER = 9;

constexpr unsigned ANIM_DELAY = 100;

constexpr int PINGUIN_RACK_COL_INTERVAL = 8;

namespace fileIndex{

constexpr unsigned NEW_PINGUIN = 100;

}

}

#endif //GAME_PINGUIN_CONSTS_H