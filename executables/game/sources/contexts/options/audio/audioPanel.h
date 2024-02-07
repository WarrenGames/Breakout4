#ifndef AUDIO_PANEL_H
#define AUDIO_PANEL_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"
#include "contexts/options/audio/soundConfig.h"
#include "contexts/options/audio/musicConfig.h"

namespace sdl2{ class RendererWindow; class Font; }
class TextsBlocks;
class PrefPathFinder;

struct AudioPanelGraphics
{
	const TextsBlocks texts;
	const sdl2::Font fancyFont;
	const TextureCombo background;
	SoundConfig sound;
	MusicConfig music;
	
	explicit AudioPanelGraphics(Essentials& essentials);
	~AudioPanelGraphics() = default;
	AudioPanelGraphics( const AudioPanelGraphics& ) = delete;
	AudioPanelGraphics& operator= ( const AudioPanelGraphics& ) = delete;
	AudioPanelGraphics( AudioPanelGraphics&& ) = default;
	AudioPanelGraphics& operator= ( AudioPanelGraphics&& ) = default;
	
	void drawAll(sdl2::RendererWindow& rndWnd) const;
	void writeDataToFile(Essentials& essentials) const;
	void updateButton(const Offset& mousePosition, bool leftButtonState);
	void updateWithButtons();
};

#endif //AUDIO_PANEL_H