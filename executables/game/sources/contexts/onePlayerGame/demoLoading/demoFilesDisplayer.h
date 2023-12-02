#ifndef CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_FILES_DISPLAYER_H
#define CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_FILES_DISPLAYER_H

#include "widgets/buttons/textButtonWidget.h"
#include "fileSystem/fileSystem.h"
#include <vector>
#include <string>

struct Essentials;
namespace sdl2{ class Font; }

namespace demosLoading{

constexpr char DemoDictionnaryFile[] = "data/demos/demosDictionary.txt";
constexpr std::size_t EntriesPerPage = 10;

struct DemoInfosData
{
	TextButton button;
	fs::path demoFilePath;
};

struct DemoFilesDisplayer
{
	std::size_t currentPage;
	std::vector< std::vector< DemoInfosData > > demoData;
	
	explicit DemoFilesDisplayer(Essentials& essentials, const sdl2::Font& font);
	~DemoFilesDisplayer() = default;
	DemoFilesDisplayer( const DemoFilesDisplayer& ) = delete;
	DemoFilesDisplayer& operator= ( const DemoFilesDisplayer& ) = delete;
	DemoFilesDisplayer( DemoFilesDisplayer&& ) = default;
	DemoFilesDisplayer& operator= ( DemoFilesDisplayer&& ) = default;
	
	void openDictionaryFile(Essentials& essentials, const sdl2::Font& font);
	void manageVectorSize();
	void addTextButtons(Essentials& essentials, const std::string& fileLine, const sdl2::Font& font);
	
	void seeNextPage();
	void seePreviousPage();
	void updateActiveButtons(const Offset& mousePosition, bool mouseLeftButtonState);
	
	void drawCurrentPage(Essentials& essentials) const;
};

}

#endif //CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_FILES_DISPLAYER_H