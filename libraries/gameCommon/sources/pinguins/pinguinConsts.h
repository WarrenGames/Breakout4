#ifndef GAME_PINGUIN_CONSTS_H
#define GAME_PINGUIN_CONSTS_H

namespace pinguin{

constexpr char TexturesListFile[] = "data/textures/pinguinTexturesList.txt";

constexpr std::size_t DirectionsNumber = 8;
constexpr std::size_t AnimFramesNumber = 9;

constexpr unsigned AnimDelay = 100;

namespace fileIndex{

constexpr unsigned NewPinguin = 100;

}

}

#endif //GAME_PINGUIN_CONSTS_H