#ifndef DUELS_BAT_CONSTS_H
#define DUELS_BAT_CONSTS_H

namespace bat{

constexpr unsigned int WingImagesNumber = 5;
constexpr int WingsFromFaceDistanceWidth = 16;
constexpr int WingsFromFaceDistanceHeight = 40;
enum{FaceEffort, FaceDisapointed, FaceHappy, FaceMax};

enum{MoveOff, MoveFromRight, MoveFromLeft};

enum{ TextureLeftWing, TextureRightWing, TextureFaces, TextureMax };

}

#endif //DUELS_BAT_CONSTS_H