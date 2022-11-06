#ifndef OPTIONS_LANGUAGES_CONTEXT_H
#define OPTIONS_LANGUAGES_CONTEXT_H

struct Essentials;
struct LanguageOptionsGraphics;

namespace langOptionsMenu{
	void context(Essentials& essentials);
	
	void useLanguagePanel(Essentials& essentials, LanguageOptionsGraphics& languagesGraphics);
	
	void updateLanguagePanel(Essentials& essentials, LanguageOptionsGraphics& languagesGraphics);
	
	void drawLanguagePanel(Essentials& essentials, const LanguageOptionsGraphics& languagesGraphics);
	
	void quitOptionsLanguagePanel(Essentials& essentials, bool& quitLanguagePanel);
}

#endif //OPTIONS_LANGUAGES_CONTEXT_H