#include "generic/texturing/backgroundDrawer.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "consts/onePlayerGridConsts.h"

BackgroundDrawer::BackgroundDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, int x_repeat, int y_repeat):
	isLoadingPerfect{true},
	drawingRepeat{ x_repeat, y_repeat },
	texture{ logs, rndWnd, texturePath, TexturePosition{} }
{
	if( false == texture.texture )
		isLoadingPerfect = false;
}

BackgroundDrawer::operator bool () const
{
	return isLoadingPerfect;
}

void BackgroundDrawer::drawBackground(sdl2::RendererWindow& rndWnd)
{
	for( int y{0} ; y < drawingRepeat.y ; ++y )
	{
		for( int x{0} ; x < drawingRepeat.x ; ++x )
		{
			texture.draw(rndWnd, x * texture.sprite.width(), y * texture.sprite.height() );
		}
	}
}