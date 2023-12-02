#ifndef OPTIONS_MENU_GRAPHICS_CONTEXT_H
#define OPTIONS_MENU_GRAPHICS_CONTEXT_H

struct Essentials;

namespace optionsMenu{
	
	class GraphicsData;
	
	namespace graphics{
		void graphicsContext(Essentials& essentials);
		
		void mainLoop(Essentials& essentials, optionsMenu::GraphicsData& graphicsData, bool& quitMenu);
	
		void update(Essentials& essentials, optionsMenu::GraphicsData& graphicsData);
	
		void drawEverything(Essentials& essentials, optionsMenu::GraphicsData& graphicsData);
	
		void quitGraphicsMenu(Essentials& essentials, bool& quitMenu);
		
		void quitWithButton(optionsMenu::GraphicsData& graphicsData, bool& quitMenu);
	
	}
}

#endif //OPTIONS_MENU_GRAPHICS_CONTEXT_H