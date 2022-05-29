#ifndef SAVES_EDITOR_FILE_LOADING_H
#define SAVES_EDITOR_FILE_LOADING_H

#include <string>

class wxTextCtrl;
struct GameSlotData;

void loadGameSlot(wxTextCtrl& logWindow, GameSlotData& slot, const std::string& gameSavePath);

#endif //SAVES_EDITOR_FILE_LOADING_H