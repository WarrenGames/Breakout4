#ifndef CREDITS_MENU_CONTEXT_H
#define CREDITS_MENU_CONTEXT_H

struct Essentials;

namespace creditsMenu{
	class GraphicsData;
	
	void context(Essentials& essentials);
	
	void mainLoop(Essentials& essentials, const creditsMenu::GraphicsData& graphicsData, bool& quitMenu);
	
	void quitMenu(Essentials& essentials, bool& quitMenu);
	
	void drawEverything(Essentials& essentials, const creditsMenu::GraphicsData& graphicsData);
}

#endif //CREDITS_MENU_CONTEXT_H