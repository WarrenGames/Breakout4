#ifndef FINAL_ACHIEVEMENT_CONTEXT_H
#define FINAL_ACHIEVEMENT_CONTEXT_H

struct Essentials;
namespace input{ class User; }
class TextButton;
struct TextureCombo;

namespace duels{

namespace finAchiev{

struct Widgets;

void mainContext(Essentials& essentials);

void mainLoop(Essentials& essentials, unsigned& finalScore, duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient);

void quitContext(bool& quitContext, input::User& inp);

void runZoneChoice(Essentials& essentials, unsigned& finalScore, const TextButton& textButton);

void quitContextWithButton(bool& quitContext, const TextButton& quitButton);

void drawEverything(Essentials& essentials, duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient);

}

}

#endif //FINAL_ACHIEVEMENT_CONTEXT_H