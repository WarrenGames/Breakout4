#ifndef OPTIONS_MENU_AUDIO_CONTEXT_H
#define OPTIONS_MENU_AUDIO_CONTEXT_H

struct Essentials;
struct AudioPanelGraphics;

namespace audioOptions{
	void mainContext(Essentials& essentials);
	
	void mainLoop(Essentials& essentials, AudioPanelGraphics& panel, bool& quitMenu);
	
	void drawEverything(Essentials& essentials, const AudioPanelGraphics& panel);
	
	void quitMenu(Essentials& essentials, bool& quitMenu);
}


#endif //OPTIONS_MENU_AUDIO_CONTEXT_H