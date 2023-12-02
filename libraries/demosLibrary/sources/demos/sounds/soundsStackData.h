#ifndef DEMOS_LIB_SOUNDS_STACK_STRUCT_DATA_H
#define DEMOS_LIB_SOUNDS_STACK_STRUCT_DATA_H

#include <chrono>

namespace demos{

struct SoundStackData
{
	std::chrono::duration<long double, std::micro> delay;
	unsigned soundEnum;
	unsigned groupTag;
	
	explicit SoundStackData();
	explicit SoundStackData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newSoundEnum, unsigned groupTagEnum);
	~SoundStackData() = default;
	SoundStackData( const SoundStackData& ) = default;
	SoundStackData& operator= ( const SoundStackData& ) = default;
	SoundStackData( SoundStackData&& ) = default;
	SoundStackData& operator= ( SoundStackData&& ) = default;
};

}

#endif //DEMOS_LIB_SOUNDS_STACK_STRUCT_DATA_H