#ifndef ONE_PLAYER_SEE_NEXT_LEVEL_H
#define ONE_PLAYER_SEE_NEXT_LEVEL_H

struct Essentials;
struct PlayerData;

namespace seeLevel{
	void context(Essentials& essentials, const PlayerData& playerData);

	void quitContext(Essentials& essentials, bool& quitLevelSketch);
}

#endif //ONE_PLAYER_SEE_NEXT_LEVEL_H