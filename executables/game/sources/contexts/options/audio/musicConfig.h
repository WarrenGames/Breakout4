#ifndef OPTIONS_MUSIC_CONFIG_H
#define OPTIONS_MUSIC_CONFIG_H

#include "widgets/buttons/textButtonWidget.h"
#include "texturing/texturesCombo.h"
#include "contexts/options/audio/volumeBar.h"
#include "wrappers/mixerPtrWrapper.h"

struct Essentials;
namespace sdl2{ class RendererWindow; class Font; }
class PrefPathFinder;
class TextsBlocks;
struct Offset;

class MusicConfig
{
private:
	bool isLoadingPerfect;
	bool isMusicActive;
	const sdl2::Mix_MusicPtr musicExample;
	const TextureCombo musicTxt;
	const TextureCombo enabled;
	const TextureCombo disabled;
	VolumeBar volBar;
	TextButton playMusic;
	TextButton switchMusicBool;
	
public:
	explicit MusicConfig(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& audioLangTexts);
	~MusicConfig() = default;
	MusicConfig( const MusicConfig& ) = delete;
	MusicConfig& operator= (const MusicConfig& ) = delete;
	MusicConfig( MusicConfig&& ) = default;
	MusicConfig& operator= ( MusicConfig&& ) = default;
	
	void writeDataFile(Essentials& essentials) const;
	bool wasLoadingPerfect() const;
	void drawAll(sdl2::RendererWindow& rndWnd) const;
	void updateButton(const Offset& mousePosition, bool buttonState);
	void updateWithButtons();
	void haltMusic() const;
	
private:
	void changeVolume(const Offset& mousePosition, bool buttonState);
	void drawMusicBooleanText(sdl2::RendererWindow& rndWnd) const;
	void invertMusicActiveBool();
	void playExampleMusic() const;
	void appendLoadedTexts(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& audioLangTexts);
	void readDataFile(Essentials& essentials);
};

#endif //OPTIONS_MUSIC_CONFIG_H