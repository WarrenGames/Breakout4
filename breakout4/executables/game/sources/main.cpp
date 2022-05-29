#include "contexts/gameStarting/initPrefPath/initPrefPath.h"
#include "SDL.h"

int main( int argc, char **argv )
{
	(void)argc;
	(void)argv;
	
	initPrefPath::startGame();

	return 0;
}