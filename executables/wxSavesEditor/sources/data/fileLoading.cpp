#include "data/fileLoading.h"
#include "gameSlots/gameSlotData.h"
#include "loading/loadData.h"
#include "fileSystem/fileSystem.h"
#include "wx/textctrl.h"
#include <fstream>
#include <stdexcept>

void loadGameSlot(wxTextCtrl& logWindow, GameSlotData& slot, const std::string& gameSavePath)
{
	if( fs::exists( gameSavePath ) )
	{
		if( std::ifstream gameSaveFile{ gameSavePath } )
		{
			try{
				gameLoading::readDataFromFile(gameSaveFile, slot);
				logWindow << "Save file: '" << gameSavePath << "' loaded with success !\n";
			}
			catch( const std::exception& e )
			{
				logWindow << "Error: couldn't load game save with path '" << gameSavePath << "' , because: " << e.what() << " .\n";
			}
		}
		else
		{
			logWindow << "Error: unable to open the game save file: '" << gameSavePath << "' \n";
		}
	}
	else{
		logWindow << "The file '" << gameSavePath << "' doesn't exist.\n";
	}
}