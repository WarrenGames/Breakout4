#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_FILE_CONTEXT_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_FILE_CONTEXT_H

struct Essentials;
struct PlayerData;

namespace demos{
	struct WriteDemoFileInterface;
	struct MainPackage;
	
	void writeDemoFileMainContext(Essentials& essentials, const PlayerData& playerData, const demos::MainPackage& mainPackage);
	
	void drawInterface(Essentials& essentials, const demos::WriteDemoFileInterface& interface);
	
	void quitInterface(Essentials& essentials, demos::WriteDemoFileInterface& interface);
	
	void writeFile(Essentials& essentials, demos::WriteDemoFileInterface& interface, const demos::MainPackage& mainPackage);
}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_FILE_CONTEXT_H