#ifndef GAME_CONTEXTS_ONE_PLAYER_GAME_DEMO_RECORDING_EDIT_BOXES_H
#define GAME_CONTEXTS_ONE_PLAYER_GAME_DEMO_RECORDING_EDIT_BOXES_H

#include "text/sdl2ttf_font.h"
#include "widgets/editBoxes/uint_editBox.h"
#include "texturing/texturesCombo.h"
#include "texts/textLoader.h"
#include <vector>

struct Essentials;
struct PlayerData;

namespace onePlGame{

namespace demoRecording{

enum{
	StickyRacket,		// = 0
	AccelerateRacket,
	EnlargeRAcket,		// = 2
	EnlargeRims,
	PowerBall,			// = 4
	OneUp,
	BonusCoinNumber,
	BonusMax			// = 7
};

class BonusesAndCoinsEdition
{
private:
	const TextsBlocks languagesTexts;
	const sdl2::Font arial;
	TextureCombo coinsText;
	std::vector< TextureCombo > bonusesHelpTexts;
	UintEditBox coinsNumberBox;
	std::vector< UintEditBox > bagBonusesBoxes;

public:
	explicit BonusesAndCoinsEdition(Essentials& essentials, PlayerData& playerData);
	~BonusesAndCoinsEdition() = default;
	BonusesAndCoinsEdition( const BonusesAndCoinsEdition& ) = delete;
	BonusesAndCoinsEdition& operator= ( const BonusesAndCoinsEdition& ) = delete;
	BonusesAndCoinsEdition( BonusesAndCoinsEdition&& ) = default;
	BonusesAndCoinsEdition& operator= ( BonusesAndCoinsEdition&& ) = default;
	
	void drawEverything(Essentials& essentials) const;
	void updateBoxesEvents(Essentials& essentials);
	
private:
	void createBonusesTexts(Essentials& essentials);
	void createBonusesBoxes(Essentials& essentials, PlayerData& playerData);
	void drawBonusesHelpTexts(Essentials& essentials) const;
	void drawBonusesBoxes(Essentials& essentials) const;
	void updateBonusesBoxesEvents(Essentials& essentials);
};

}

}

#endif //GAME_CONTEXTS_ONE_PLAYER_GAME_DEMO_RECORDING_EDIT_BOXES_H