#ifndef FINAL_ACHIEVEMENT_CONTEXT_H
#define FINAL_ACHIEVEMENT_CONTEXT_H

struct Essentials;
namespace input{ class User; }
class TextButton;
struct TextureCombo;

namespace duels{

namespace finAchiev{

struct Widgets;

void mainContext(Essentials& essentials, unsigned& finalScore, bool& quitDuels);

void mainLoop(Essentials& essentials, duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient, bool& quitDuels);

void quitContext(input::User& inp, bool& quitDuels, bool& quitContext);

void runZoneChoice(const TextButton& textButton, bool& quitContext);

void quitContextWithButton(const TextButton& quitButton, bool& quitDuels, bool& quitContext);

void drawEverything(Essentials& essentials, const duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient);

}

}

#endif //FINAL_ACHIEVEMENT_CONTEXT_H