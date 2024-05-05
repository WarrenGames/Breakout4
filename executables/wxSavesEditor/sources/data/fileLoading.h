#ifndef SAVES_EDITOR_FILE_LOADING_H
#define SAVES_EDITOR_FILE_LOADING_H

#include "fileSystem/fileSystem.h"

class wxTextCtrl;
struct GameSlotData;

void loadGameSlot(wxTextCtrl& logWindow, GameSlotData& slot, const fs::path& gameSavePath);

#endif //SAVES_EDITOR_FILE_LOADING_H