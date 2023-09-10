#ifndef ONE_PLAYER_CAMPAIGN_EDN_INTERFACE_H
#define ONE_PLAYER_CAMPAIGN_EDN_INTERFACE_H

#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "texturing/texturesCombo.h"
#include "texts/textLoader.h"

struct Essentials;
struct PlayerData;

namespace onePlGame{

namespace campaignEnd{

enum{ EndAnnouncement, HereIsYourScore, CheckUpdateOut, Max };
	
struct Interface
{
	const sdl2::Font fancyFont;
	const TextsBlocks localTexts;
	const TextureCombo wallpaper;
	const TextureCombo scoreText;
	const TextureCombo greatings;
	const TextureCombo checkOutWebSite;
	
	Interface(Essentials& essentials, const PlayerData& playerData);
	~Interface() = default;
	Interface( const Interface& ) = delete;
	Interface& operator= ( const Interface& ) = delete;
	Interface( Interface&& ) = default;
	Interface& operator= ( Interface&& ) = default;

	void drawEverything(Essentials& essentials) const;
};

}

}

#endif //ONE_PLAYER_CAMPAIGN_EDN_INTERFACE_H