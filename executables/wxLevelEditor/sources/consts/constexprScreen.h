#ifndef CONSTEXPR_SCREEN_H
#define CONSTEXPR_SCREEN_H

constexpr int SQR_SIZE = 48;

constexpr int EditorGridSquaresWidth = 20;
constexpr int EditorGridSquaresHeight = 15;
constexpr int EditorBrickElementsSquaresWidth = 6;
constexpr int EditorBrickElementsSquaresHeight = 7;

constexpr int BrickElementsWidth = EditorBrickElementsSquaresWidth * SQR_SIZE;
constexpr int BrickElementsHeight = EditorBrickElementsSquaresHeight * SQR_SIZE;

constexpr int EditorGridWidth = SQR_SIZE * EditorGridSquaresWidth;
constexpr int EditorGridHeight = SQR_SIZE * EditorGridSquaresHeight;

constexpr int EditorWindowWidth = EditorGridWidth + BrickElementsWidth;
constexpr int EditorWindowHeight = EditorGridHeight + SQR_SIZE * 4;

constexpr int LogWindowWidth = EditorWindowWidth;
constexpr int LogWindowHeight = 256;

#endif //CONSTEXPR_SCREEN_H