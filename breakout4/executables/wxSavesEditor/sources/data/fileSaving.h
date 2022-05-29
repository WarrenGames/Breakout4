#ifndef SAVES_EDITOR_FILE_SAVING_H
#define SAVES_EDITOR_FILE_SAVING_H

#include <string>

class wxTextCtrl;
struct GameSlotData;

void saveGameSlot(wxTextCtrl& logWindow, const GameSlotData& slot, const std::string& gameSavePath);

#endif //SAVES_EDITOR_FILE_SAVING_H