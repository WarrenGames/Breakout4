#include "levelComponents/global/monstersTriggers.h"
#include <cassert>

MonsterTrigger::MonsterTrigger():
	triggers(Max_monster_trigger, false)
{
	
}

bool MonsterTrigger::canTrigger(std::size_t index) const
{
	assert( index < triggers.size() );
	return triggers[index];
}

void MonsterTrigger::setTriggerFlag(std::size_t index, bool value)
{
	assert( index < triggers.size() );
	triggers[index] = value;
}