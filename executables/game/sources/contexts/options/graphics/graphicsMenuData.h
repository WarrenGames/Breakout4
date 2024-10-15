#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "widgets/editBoxes/uint_editBox.h"
#include "widgets/editBoxes/bool_editBox.h"
#include "texturing/texturesCombo.h"
#include "widgets/buttons/textButtonWidget.h"

struct Essentials;

namespace optionsMenu{
	
class GraphicsData
{
private:
	TextsBlocks languagesTexts;
	sdl2::Font fancyFont;
	unsigned framePerSecond;
	UintEditBox frameEditBox;
	bool displaySdl2Logo;
	BoolEditBox displayLogoEditBox;
	TextureCombo panelTitle;
	TextureCombo displayLogoInfoText;
	TextureCombo boxName;
	TextureCombo hintOnFrame;
	TextureCombo screenBackground;
	TextButton quitButton;
	
public:
	explicit GraphicsData(Essentials& essentials);
	~GraphicsData() = default;
	GraphicsData( const GraphicsData& ) = delete;
	GraphicsData& operator= ( const GraphicsData& ) = delete;
	GraphicsData( GraphicsData&& ) = default;
	GraphicsData& operator= ( GraphicsData&& ) = default;

	void updateBox(Essentials& essentials);
	void drawEverything(Essentials& essentials) const;
	void writeDataToFiles(Essentials& essentials) const;
	unsigned getFramePerSecond() const;
	bool quitButtonClicked() const;
	
private:
	void writeFramePerSecondData(Essentials& essentials) const;
	void writeSdl2LogoDisplaying(Essentials& essentials) const;
	void readSdl2LogoDisplayingFile(Essentials& essentials);
};

}