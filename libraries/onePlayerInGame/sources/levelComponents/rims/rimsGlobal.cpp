#include "levelComponents/rims/rimsGlobal.h"
#include "types/essentialsStruct.h"
#include "consts/rimsConsts.h"

constexpr char RimTexturePath[] = "textures/sprites/bricks/purpleRim.png";
constexpr int RimPointsDisplayDuration = 2500;

OnePlayerRimsSystem::OnePlayerRimsSystem(Essentials& essentials, int rimsStartState):
	rimTexture{ essentials.logs, essentials.rndWnd, RimTexturePath },
	rimsState{ rimsStartState },
	rimsScoreValueDrawing{ essentials, rimsScoresStock },
	textIndex{ 0 },
	canDrawBonusText{ false }
{

}

std::vector<SDL_Rect>::const_iterator OnePlayerRimsSystem::begin() const
{
	return rimsState.begin();
}

std::vector<SDL_Rect>::const_iterator OnePlayerRimsSystem::end() const
{
	return rimsState.end();
}

void OnePlayerRimsSystem::rimsUpdate()
{
	rimsState.update();
	updateDrawBoolValue();
	declareRimAppeared();
}

int OnePlayerRimsSystem::getRimsStatus() const
{
	return rimsState.getRimsStatus();
}

void OnePlayerRimsSystem::changeStatus(int change)
{
	rimsState.changeStatus(change);
	stockScore(change);
}

void OnePlayerRimsSystem::updateDrawBoolValue()
{
	if( pointsInfosDuration.hasTimeElapsed(std::chrono::milliseconds{ RimPointsDisplayDuration }))
	{
		pointsInfosDuration.joinTimePoints();
		canDrawBonusText = false;
	}
}

void OnePlayerRimsSystem::setDrawBonusTextFlag()
{
	canDrawBonusText = true;
	pointsInfosDuration.joinTimePoints();
	switch (rimsState.getRimsStatus())
	{
	case rims::Remove1stRim:
		activeNewTextOrDefaultOne(rimsState.getRimsStatus());
		break;
	case rims::Remove2ndRim:
		activeNewTextOrDefaultOne(rimsState.getRimsStatus());
		break;
	case rims::Remove3rdRim:
		activeNewTextOrDefaultOne(rimsState.getRimsStatus());
		break;
	default:
		textIndex = rims::RemoveMax;
		break;
	}
}

void OnePlayerRimsSystem::declareRimAppeared()
{
	if( rimsState.getRimsStatus() >= rims::Remove1stRim && rimsState.getRimsStatus() <= rims::Remove3rdRim )
	{
		if( rimsState.getRimMovement(rimsState.getRimsStatus()) == rims::RimGoesUp )
		{
			setRimWasActiveOnce(rimsState.getRimMovement(rimsState.getRimsStatus() ) );
		}
	}
}

int OnePlayerRimsSystem::getReservedScoreIfAny()
{
	return rimsScoresStock.getReservedScoreIfAny();
}

void OnePlayerRimsSystem::drawRims(Essentials& essentials)
{
	for( auto const &rimOffset : rimsState )
	{
		rimTexture.draw(essentials.rndWnd, rimOffset.x, rimOffset.y);
	}
}

void OnePlayerRimsSystem::drawPointsText(Essentials& essentials) const

{
	if( canDrawBonusText )
	{
		if( textIndex < rims::RemoveMax )
		{
			if( canDrawBonusText && (rimsState.getRimMovement(textIndex) == rims::RimIsStatic || rimsState.getRimMovement(textIndex) == rims::RimGoesUp))
			{
				rimsScoreValueDrawing.drawText(essentials, textIndex);
			}
		}
		else{
			assert( textIndex == rims::RemoveMax );
			rimsScoreValueDrawing.drawText( essentials, textIndex );
		}
	}
}

void OnePlayerRimsSystem::setRimWasActiveOnce(int change)
{
	if( change >= 1 )
	{
		switch( rimsState.getRimsStatus() )
		{
			case rims::Remove1stRim:
				rimsPast.setBorderToActiveOne( static_cast<std::size_t>(rims::Remove1stRim) );
				break;
			case rims::Remove2ndRim:
				rimsPast.setBorderToActiveOne( static_cast<std::size_t>(rims::Remove2ndRim) );
				break;
			case rims::Remove3rdRim:
				rimsPast.setBorderToActiveOne( static_cast<std::size_t>(rims::Remove3rdRim) );
				break;
		}
	}
}

void OnePlayerRimsSystem::activeNewTextOrDefaultOne(int status)
{
	if( status >= rims::Remove1stRim && status <= rims::Remove3rdRim )
	{
		if( rimsPast.wasBorderAlreadyActivated(status) )
		{
			textIndex = rims::PointsDefault;
		}
		else{
			textIndex = static_cast<std::size_t>( status );
		}
	}
}

void OnePlayerRimsSystem::stockScore(int change)
{
	if( change == 1 && rimsState.getRimsStatus() >= rims::Remove1stRim && rimsState.getRimsStatus() < rims::RemoveMax )
	{
		if( rimsState.getRimsStatus() >= 0 
			&& rimsState.getRimsStatus() < static_cast<int>( rimsPast.size() ) 
			&& false == rimsPast.wasBorderAlreadyActivated(rimsState.getRimsStatus() ) )
		{
			rimsScoresStock.stockGivenScore(rimsState.getRimsStatus() );
		}
		else{
			rimsScoresStock.stockDefaultScore();
		}
	}
}