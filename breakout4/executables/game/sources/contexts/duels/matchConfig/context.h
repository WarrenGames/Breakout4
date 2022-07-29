#ifndef DUELS_ZONE_CHOICE_CONTEXT_H
#define DUELS_ZONE_CHOICE_CONTEXT_H

struct ZoneChoiceThings;
struct Essentials;
namespace input{ class User; }
namespace sdl2{ class RendererWindow; }
class TextButton;

namespace duels{
	struct LevelOptions;
namespace matchConfig{
		
void context(Essentials& essentials, unsigned finalScore);

void quitContext(bool& quitContext, input::User& inp);

void update(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings);

void drawEverything(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings);

void runInputConfigurationScreen(Essentials& essentials, const TextButton& inputScreenBtn);

void runChosenZone(Essentials& essentials, unsigned finalScore, ZoneChoiceThings& zoneThings);

void zoneChoiceWithIndex(Essentials& essentials, unsigned finalScore, ZoneChoiceThings& zoneThings);

void zoneConfig(Essentials& essentials, ZoneChoiceThings& zoneThings);

void zonesChoiceInterface(Essentials& essentials, ZoneChoiceThings& zoneThings);

void bonusesConfigInterface(Essentials& essentials, ZoneChoiceThings& zoneThings);

void stopConfigBecauseOfWinner(unsigned finalScore, const duels::LevelOptions& levelOptions, bool& quitMatchConfig);

}

}

#endif //DUELS_ZONE_CHOICE_CONTEXT_H