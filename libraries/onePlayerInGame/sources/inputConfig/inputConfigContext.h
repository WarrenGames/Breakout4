#ifndef ONE_PLAYER_INPUT_CONFIG_H
#define ONE_PLAYER_INPUT_CONFIG_H

struct Essentials;
namespace onePlGame{ struct InputThings; }

namespace onePlInputCfg{
	void mainContext(Essentials& essentials);
	
	void quitInputConfigContext(bool& quit, Essentials& essentials);
	
	void goToJoystickMenu(Essentials& essentials, onePlGame::InputThings& inputThings);
}

#endif //ONE_PLAYER_INPUT_CONFIG_H