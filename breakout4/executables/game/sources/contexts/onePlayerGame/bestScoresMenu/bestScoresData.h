#ifndef ONE_PLAYER_BEST_SCORES_INTERFACE_H
#define ONE_PLAYER_BEST_SCORES_INTERFACE_H

#include "consts/onePlayerLevelConsts.h"
#include <string>
#include <vector>

struct Essentials;

struct ScoreSample
{
	unsigned score;
	std::string date;
	bool scoreFromLastGame;
	
	explicit ScoreSample();
	explicit ScoreSample(unsigned readScore, const std::string& readDate);
	explicit ScoreSample(unsigned lastGameScore);
	~ScoreSample() = default;
	
	std::string getText() const;
};

class BestScoresData
{
private:
	std::vector< std::vector< ScoreSample > > scores;
	unsigned campaignTypeValue;
	bool isLoadingPerfect;
	
public:
	//Constructor used when the user just wants to see the actual scores
	explicit BestScoresData(Essentials& essentials, unsigned campaignType);
	
	//Constructor used when the user has ended a game with possibility of adding a new score
	explicit BestScoresData(Essentials& essentials, unsigned campaignType, unsigned lastGameScore, unsigned skill, unsigned scoreCampaignType);
	~BestScoresData() = default;
	BestScoresData( const BestScoresData& ) = delete;
	BestScoresData& operator= ( const BestScoresData& ) = delete;
	BestScoresData( BestScoresData&& ) = default;
	BestScoresData& operator= ( BestScoresData&& ) = default;

	const ScoreSample& getSample(std::size_t skill, std::size_t scoreNumber) const;
	std::size_t getScoresNumber(std::size_t skill) const;
	void startSaving(Essentials& essentials) const;

private:
	void saveScoresToFile(Essentials& essentials, const std::string& scoreFilePath, unsigned skill) const;
	void loadScores(Essentials& essentials, unsigned campaignType);
	void loadScoresList(Essentials& essentials, unsigned skillNumber, const std::string& scoreFilePath);
	void addScoreFromLastGame(unsigned lastGameScore, unsigned skill, unsigned scoreCampaignType);
	void sortAllScoresArrays();
};

#endif //ONE_PLAYER_BEST_SCORES_INTERFACE_H