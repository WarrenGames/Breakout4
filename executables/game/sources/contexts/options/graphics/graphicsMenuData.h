#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "widgets/editBoxes/uint_editBox.h"
#include "texturing/texturesCombo.h"
#include "widgets/buttons/textButtonWidget.h"

struct Essentials;

namespace optionsMenu{
	
class GraphicsData
{
private:
	const TextsBlocks languagesTexts;
	const sdl2::Font fancyFont;
	unsigned framePerSecond;
	UintEditBox frameEditBox;
	const TextureCombo panelTitle;
	const TextureCombo boxName;
	const TextureCombo hintOnFrame;
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
	
	void writeFramePerSecondData(Essentials& essentials) const;
	unsigned getFramePerSecond() const;
	bool quitButtonClicked() const;
};

}