#ifndef BAG_ICONS_POSITIONS_LOADER_H
#define BAG_ICONS_POSITIONS_LOADER_H

#include "customTypes/positionTypes.h"
#include <vector>
#include <string>

struct AppLogFiles;

class BagIconsPositions
{
private:
	std::vector< Offset > positions;
	bool isLoadingPerfect;
	
public:
	explicit BagIconsPositions(AppLogFiles& logs, const std::string& filePath);
	~BagIconsPositions() = default;
	BagIconsPositions( const BagIconsPositions& ) = delete;
	BagIconsPositions& operator= ( BagIconsPositions& ) = delete;
	
	bool wasLoadingPerfect() const;
	
	const Offset& operator []( std::size_t index ) const;
	std::size_t size() const;
	
private:
	void loadData(AppLogFiles& logs, const std::string& filePath);
	void convertValueIfNeeded(Offset& offset) const;
};

#endif //BAG_ICONS_POSITIONS_LOADER_H