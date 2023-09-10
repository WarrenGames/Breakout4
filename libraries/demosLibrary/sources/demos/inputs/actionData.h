#ifndef DEMOS_LIB_INPUTS_ACTION_DATA_H
#define DEMOS_LIB_INPUTS_ACTION_DATA_H

#include <chrono>

namespace demos{

struct ActionData
{
	std::chrono::duration<long double, std::micro> delay;
	unsigned funcEnum;
	bool actionState;
	
	explicit ActionData();
	explicit ActionData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newFunc, bool action);
	~ActionData() = default;
	ActionData( const ActionData& ) = default;
	ActionData& operator= ( const ActionData& ) = default;
};

}

#endif //DEMOS_LIB_INPUTS_ACTION_DATA_H