#include "contexts/options/audio/audioPanel.h"
#include "prefPath/prefPathFinder.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texturing/texturePosition.h"
#include "types/essentialsStruct.h"
#include "consts/fontsConsts.h"
#include "consts/optionsLanguageConsts.h"

AudioPanelGraphics::AudioPanelGraphics(Essentials& essentials):
	texts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OptionMenuAudioPanel), audioLang::Max},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	background{essentials.logs, essentials.rndWnd, "textures/gameGUI/optionsVignettes/audioBackground.png", TexturePosition{ 0, 0 } },
	sound{essentials, fancyFont, texts},
	music{essentials, fancyFont, texts}
{
	
}

void AudioPanelGraphics::drawAll(sdl2::RendererWindow& rndWnd) const
{
	background.draw(rndWnd);
	sound.drawAll(rndWnd);
	music.drawAll(rndWnd);
}

void AudioPanelGraphics::writeDataToFile(Essentials& essentials) const
{
	sound.writeDataFile(essentials);
	music.writeDataFile(essentials);
}

void AudioPanelGraphics::updateButton(const Offset& mousePosition, bool buttonState)
{
	sound.updateButton(mousePosition, buttonState);
	music.updateButton(mousePosition, buttonState);
}

void AudioPanelGraphics::updateWithButtons()
{
	sound.updateWithButtons();
	music.updateWithButtons();
}