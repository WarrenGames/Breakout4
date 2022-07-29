#ifndef MAKE_INPUT_STRING_FROM_DATA_H
#define MAKE_INPUT_STRING_FROM_DATA_H

#include <string>
#include <memory>

class TextsBlocks;

namespace duels{

struct InputEntity;

std::string getStringFromDeviceType(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts);

std::string getStringFromLeftMove(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts);

std::string getStringFromRightMove(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts);

std::string getStringFromActiveBonus(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts);

std::string getStringFromZoneSpecific(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts);

std::string getStringFromJoystickMove(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts);

}

#endif //MAKE_INPUT_STRING_FROM_DATA_H