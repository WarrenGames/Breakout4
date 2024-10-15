#ifndef ONE_PLAYER_GAME_MONSTERS_TRIGGERS_H
#define ONE_PLAYER_GAME_MONSTERS_TRIGGERS_H

#include <vector>

enum{
	Pinguin_monster_trigger,
	Hell_skull_monster_trigger,
	Max_monster_trigger
};

class MonsterTrigger
{
private:
	std::vector< bool > triggers;
	
public:
	explicit MonsterTrigger();
	~MonsterTrigger() = default;
	MonsterTrigger( const MonsterTrigger& ) = delete;
	MonsterTrigger& operator= ( const MonsterTrigger& ) = delete;
	MonsterTrigger( MonsterTrigger&& ) = default;
	MonsterTrigger& operator= ( MonsterTrigger&& ) = default;
	
	bool canTrigger(std::size_t index) const;
	void setTriggerFlag(std::size_t index, bool value);
};

#endif //ONE_PLAYER_GAME_MONSTERS_TRIGGERS_H