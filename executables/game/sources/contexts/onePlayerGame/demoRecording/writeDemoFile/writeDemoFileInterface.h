#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_FILE_INTERFACE_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_FILE_INTERFACE_H

#include "widgets/editBoxes/stringEditBox.h"
#include "widgets/buttons/textButtonWidget.h"
#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include <string>
#include <vector>

struct Essentials;
struct PlayerData;

namespace demos{
	struct MainPackage;
	
	enum{ 	
		WriteTitle,
		WriteFileName,
		WriteSaveFileToDisk,
		WriteSavingDirectory,
		WriteQuitInterface,
		WriteMax
	};
	
	struct WriteDemoFileInterface
	{
		const TextsBlocks languagesTexts;
		const sdl2::Font fancyFont;
		const sdl2::Font arialFont;
		std::string fileName;
		TextureCombo titleText;
		TextureCombo fileNameText;
		StringEditBox fileNameEditBox;
		TextButton saveButton;
		TextButton quitButton;
		TextureCombo savingDirectory;
		std::vector< TextureCombo > stacksSumStrings;
		bool quit;
		
		explicit WriteDemoFileInterface(Essentials& essentials, const PlayerData& playerData, const demos::MainPackage& mainPackage);
		~WriteDemoFileInterface() = default;
		WriteDemoFileInterface( const WriteDemoFileInterface& ) = delete;
		WriteDemoFileInterface& operator= ( const WriteDemoFileInterface& ) = delete;
		WriteDemoFileInterface( WriteDemoFileInterface&& ) = default;
		WriteDemoFileInterface& operator= ( WriteDemoFileInterface&& ) = default;
		
		void drawEverything(Essentials& essentials) const;
		void updateInterface(Essentials& essentials);
		
		void makeStackStrings(Essentials& essentials, const demos::MainPackage& mainPackage);
		void drawStacksStrings(Essentials& essentials) const;
	};
}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_FILE_INTERFACE_H