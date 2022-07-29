#ifndef RACE_LEVELS_COUNT_H
#define RACE_LEVELS_COUNT_H

#include <string>

struct Essentials;

class RaceLevelsCount
{
private:
	unsigned levelsCount;
	bool isLoadingPerfect;
	
public:
	RaceLevelsCount(Essentials& essentials, const std::string& mainFilePath);
	~RaceLevelsCount() = default;
	RaceLevelsCount( const RaceLevelsCount& ) = delete;
	RaceLevelsCount& operator= ( const RaceLevelsCount& ) = delete;
	RaceLevelsCount( RaceLevelsCount&& ) = default;
	RaceLevelsCount& operator= ( RaceLevelsCount&& ) = default;
	
	
	operator bool() const;
	unsigned getLevelsNumber() const;
	
private:
	void loadFile(Essentials& essentials, const std::string& mainFilePath);
};

#endif //RACE_LEVELS_COUNT_H