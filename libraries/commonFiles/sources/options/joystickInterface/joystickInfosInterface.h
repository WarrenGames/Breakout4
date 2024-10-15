#ifndef JOYSTICK_INFOS_INTERFACE_H
#define JOYSTICK_INFOS_INTERFACE_H

struct Essentials;
class JoystickValuesTextures;
namespace sdl2{ class JoystickEntity; class Font; }

namespace joyCfg{

	void mainContext(Essentials& essentials, const sdl2::Font& arial, const sdl2::JoystickEntity& joyEnt);

	void mainLoop(Essentials& essentials, JoystickValuesTextures& joystickTextures);
}

#endif //JOYSTICK_INFOS_INTERFACE_H