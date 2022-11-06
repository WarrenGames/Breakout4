#ifndef RACKET_FREEZES_DURATIONS_LOADER_H
#define RACKET_FREEZES_DURATIONS_LOADER_H

#include <vector>
#include <string>

struct Essentials;

namespace freezes{

constexpr char OnePlayerFilePath[] = "data/levels/1player/options/racketFreezeDuration.cfg";

class FreezeDurations
{
private:
	std::vector< unsigned > durations;
	bool wasLoadingPerfect;

public:
	explicit FreezeDurations(Essentials& essentials, const std::string& configFilePath, std::size_t durationsCount);
	~FreezeDurations() = default;
	FreezeDurations( const FreezeDurations& ) = delete;
	FreezeDurations& operator= ( const FreezeDurations& ) = delete;
	FreezeDurations( FreezeDurations&& ) = default;
	FreezeDurations& operator= ( FreezeDurations&& ) = default;
	
	operator bool() const;
	unsigned getDuration(std::size_t arrayIndex) const;
	std::size_t size() const;
	
private:
	void openConfigFile(Essentials& essentials, const std::string& configFilePath, std::size_t durationsCount);
};

}

#endif //RACKET_FREEZES_DURATIONS_LOADER_H