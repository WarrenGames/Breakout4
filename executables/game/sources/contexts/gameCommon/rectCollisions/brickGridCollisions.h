#ifndef DUELS_LEVEL_GRID_INSTRUCTIONS_H
#define DUELS_LEVEL_GRID_INSTRUCTIONS_H

template<typename T>class MatrixTemp2D;
struct BrickData;
namespace spriteMove{ class ObjectMoving; }
struct Offset;
struct SpriteSize;
class SoundHandler;

bool isThereAnElementAtThisPosition(const MatrixTemp2D<BrickData>& levelGrid, const spriteMove::ObjectMoving& move, const Offset& add);

bool canCollideWithGridLeft(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval);
bool canCollideWithGridRight(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval );
bool canCollideWithGridTop(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval);
bool canCollideWithGridBottom(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval);

void testGridCollisions(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);

void testCollideWithTopElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);
void testCollideWithBottomElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);
void testCollideWithLeftElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);
void testCollideWithRightElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);

void testCollideWithTopLeftCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);
void testCollideWithTopRightCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);
void testCollideWithBottomLeftCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);
void testCollideWithBottomRightCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol);

#endif //DUELS_LEVEL_GRID_INSTRUCTIONS_H