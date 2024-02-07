#include "data/fileLoading.h"
#include "gameSlots/gameSlotData.h"
#include "loading/loadData.h"
#include "fileSystem/fileSystem.h"
#include "wx/textctrl.h"
#include <fstream>
#include <stdexcept>

void loadGameSlot(wxTextCtrl& logWindow, GameSlotData& slot, const fs::path& gameSavePath)
{
	if( fs::exists( gameSavePath ) )
	{
		if( std::ifstream gameSaveFile{ gameSavePath } )
		{
			try{
				gameLoading::readDataFromFile(gameSaveFile, slot);
				logWindow << "Save file: '" << gameSavePath.string() << "' loaded with success !\n";
			}
			catch( const std::exception& e )
			{
				logWindow << "Error: couldn't load game save with path '" << gameSavePath.string() << "' , because: " << e.what() << " .\n";
			}
		}
		else
		{
			logWindow << "Error: unable to open the game save file: '" << gameSavePath.string() << "' \n";
		}
	}
	else{
		logWindow << "The file '" << gameSavePath.string() << "' doesn't exist.\n";
	}
}