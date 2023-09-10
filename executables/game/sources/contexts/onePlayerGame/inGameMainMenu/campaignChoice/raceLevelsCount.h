#ifndef RACE_LEVELS_COUNT_H
#define RACE_LEVELS_COUNT_H

#include "fileSystem/fileSystem.h"

struct Essentials;

class RaceLevelsCount
{
private:
	unsigned levelsCount;
	bool isLoadingPerfect;
	
public:
	RaceLevelsCount(Essentials& essentials, const fs::path& mainFilePath);
	~RaceLevelsCount() = default;
	RaceLevelsCount( const RaceLevelsCount& ) = delete;
	RaceLevelsCount& operator= ( const RaceLevelsCount& ) = delete;
	RaceLevelsCount( RaceLevelsCount&& ) = default;
	RaceLevelsCount& operator= ( RaceLevelsCount&& ) = default;

	operator bool() const;
	unsigned getLevelsNumber() const;
	
private:
	void loadFile(Essentials& essentials, const fs::path& mainFilePath);
};

#endif //RACE_LEVELS_COUNT_H