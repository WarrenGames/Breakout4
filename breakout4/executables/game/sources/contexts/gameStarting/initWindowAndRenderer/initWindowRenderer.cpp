#include "contexts/gameStarting/initWindowAndRenderer/initWindowRenderer.h"
#include "texturing/rendererWindow.h"
#include "logging/logsStruct.h"
#include "contexts/gameStarting/startMiniScreen/startMiniScreenContext.h"
#include "consts/constexprScreen.h"

constexpr char ICON_PATH[] = "textures/sprites/balls/yellowBall.png";

void cntxt::windRend::create(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& chosenLang)
{
	sdl2::RendererWindow rndWnd{logs.error, SCREENW_MINI, SCREENH_MINI, GAME_WINDOW_TITLE, ICON_PATH};
	
	if( rndWnd.wasInitializationPerfect() )
	{
		cntxt::miniScreen::mainContext(logs, prefPath, chosenLang, rndWnd);
	}
}