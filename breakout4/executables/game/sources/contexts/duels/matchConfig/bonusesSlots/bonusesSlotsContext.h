#ifndef DUELS_BONUSES_SLOTS_CONTEXT_H
#define DUELS_BONUSES_SLOTS_CONTEXT_H

struct Essentials;
struct ZoneChoiceThings;

namespace duels{

struct BonusesInterface;
	
namespace bonuses{
	void context(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings);
	
	void mainLoop(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, BonusesInterface& interface, bool& quitMenu);
	
	void quitContext(Essentials& essentials, bool& quitMenu);
	
	void writeDataWithButtons(Essentials& essentials, const BonusesInterface& interface);
	
	void loadSlot(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, const BonusesInterface& interface, bool& quitMenu);
	
	void drawEverything(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, BonusesInterface& interface, bool quitMenu);
	
	void quitWithButton(const BonusesInterface& interface, bool& quitMenu);
}

}

#endif //DUELS_BONUSES_SLOTS_CONTEXT_H