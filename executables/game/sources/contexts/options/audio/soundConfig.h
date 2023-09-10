#ifndef SOUNDCONFIG_H
#define SOUNDCONFIG_H

#include "widgets/buttons/textButtonWidget.h"
#include "texturing/texturesCombo.h"
#include "contexts/options/audio/volumeBar.h"
#include "wrappers/mixerPtrWrapper.h"

struct Essentials;
namespace sdl2{ class RendererWindow; class Font; }
class TextsBlocks;
struct Offset;

class SoundConfig
{
private:
	bool isLoadingPerfect;
	bool isSoundActive;
	const sdl2::Mix_ChunkPtr soundExample;
	const TextureCombo soundsTxt;
	const TextureCombo enabled;
	const TextureCombo disabled;
	VolumeBar volBar;
	TextButton playSound;
	TextButton switchSoundBool;

public:
	explicit SoundConfig(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& audioLangTexts);
	~SoundConfig();
	SoundConfig( const SoundConfig& ) = delete;
	SoundConfig& operator= ( const SoundConfig& ) = delete;
	SoundConfig( SoundConfig&& ) = default;
	SoundConfig& operator= ( SoundConfig&& ) = default;
	
	void writeDataFile(Essentials& essentials) const;
	bool wasLoadingPerfect() const;
	void drawAll(sdl2::RendererWindow& rndWnd) const;
	void updateButton(const Offset& mousePosition, bool buttonState);
	void updateWithButtons();
	
private:
	void changeVolume(const Offset& mousePosition, bool buttonState);
	void drawSoundBooleanText(sdl2::RendererWindow& rndWnd) const;
	void invertSoundActiveBool();
	void playExampleSound() const;
	void readDataFile(Essentials& essentials);
};

#endif//SOUNDCONFIG_H