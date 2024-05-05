#ifndef DUELS_INPUTS_CONSTS_H
#define DUELS_INPUTS_CONSTS_H

namespace duels{

enum{DeviceKeyboard, DeviceJoystick1, DeviceJoystick2, DeviceMax };

enum{JoystickMoveAxes, JoystickMoveHats, JoystickMoveError};

enum{JoystickBonusButton, JoystickZoneSpecificButton, JoystickButtonMax};

enum{InputMoveLeft, InputMoveRight, InputActiveBonus, InputZoneSpecific, InputMax};

enum{KeyLeft, KeyRight, KeyActiveBonus, KeyZoneSpecific, KeyMax};

}

#endif //DUELS_INPUTS_CONSTS_H