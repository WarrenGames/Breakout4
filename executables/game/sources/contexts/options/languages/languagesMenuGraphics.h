#ifndef LANGUAGES_MENU_GRAPHICS_H
#define LANGUAGES_MENU_GRAPHICS_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"
#include "widgets/buttons/textButtonWidget.h"
#include "fileSystem/fileSystem.h"
#include <string>
#include <vector>

struct Essentials;

struct LanguageOptionsGraphics
{
	bool isLoadingPerfect;
	bool hasLanguageChanged;
	std::size_t langIndex;
	const TextsBlocks languagesStrings;
	const sdl2::Font fancyFont;
	std::vector< TextButton > languagesButtons;
	std::vector< TextureCombo > languagesTexts;
	const TextureCombo startingLanguage;
	const TextureCombo screenTitle;
	const TextureCombo restartHint;
	const TextureCombo selectHere;
	std::vector< std::string > languagesList;
	
	explicit LanguageOptionsGraphics(Essentials& essentials);
	~LanguageOptionsGraphics() = default;
	LanguageOptionsGraphics( const LanguageOptionsGraphics& ) = delete;
	LanguageOptionsGraphics& operator= ( const LanguageOptionsGraphics& ) = delete;
	LanguageOptionsGraphics( LanguageOptionsGraphics&& ) = default;
	LanguageOptionsGraphics& operator= ( LanguageOptionsGraphics&& ) = default;
	
	void drawEverything(Essentials& essentials) const;
	void drawButtons(Essentials& essentials) const;
	void drawSelectedLanguage(Essentials& essentials) const;
	void update(Essentials& essentials);
	void loadAvailableLanguages(Essentials& essentials, const fs::path& languagesListPath);
	void changeLanguage();
	
	void writeNewLanguageIfChanged(Essentials& essentials);
};

#endif //LANGUAGES_MENU_GRAPHICS_H