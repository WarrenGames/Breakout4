#include "data/fileSaving.h"
#include "gameSlots/gameSlotData.h"
#include "saving/saveData.h"
#include "wx/textctrl.h"
#include <fstream>
#include <stdexcept>

void saveGameSlot(wxTextCtrl& logWindow, const GameSlotData& slot, const std::string& gameSavePath)
{
	if( std::ofstream saveFile{ gameSavePath } )
	{
		try{ 
			gameSaving::writeDataToFile(saveFile, slot);
			logWindow << "Slot saves with success in '" << gameSavePath << "' file.\n";
		}
		catch( const std::exception& e )
		{
			logWindow << "Error while saving file: " << e.what() << " .\n";
		}
	}
	else{
		logWindow << "Error: couldn't open this file to save game data: '" << gameSavePath << "' \n";
	}
}