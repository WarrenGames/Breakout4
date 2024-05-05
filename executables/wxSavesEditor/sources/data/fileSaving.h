#ifndef SAVES_EDITOR_FILE_SAVING_H
#define SAVES_EDITOR_FILE_SAVING_H

#include "fileSystem/fileSystem.h"

class wxTextCtrl;
struct GameSlotData;

void saveGameSlot(wxTextCtrl& logWindow, const GameSlotData& slot, const fs::path& gameSavePath);

#endif //SAVES_EDITOR_FILE_SAVING_H