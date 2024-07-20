cmake_minimum_required( VERSION 3.13 )

project( breakout4_game LANGUAGES CXX )

set( HEADERS
	sources/contexts/options/graphics/graphicsMenuData.h
	sources/contexts/options/graphics/graphicsOptionsConsts.h
	sources/contexts/options/graphics/graphicsContext.h
	sources/contexts/options/mainMenuData.h
	sources/contexts/options/mainMenuConsts.h
	sources/contexts/options/audio/volumeBar.h
	sources/contexts/options/audio/audioPanel.h
	sources/contexts/options/audio/soundConfig.h
	sources/contexts/options/audio/audioContext.h
	sources/contexts/options/audio/musicConfig.h
	sources/contexts/options/optionsContext.h
	sources/contexts/options/languages/languageContext.h
	sources/contexts/options/languages/languagesMenuGraphics.h
	sources/contexts/gameStarting/startMiniScreen/startMiniScreenContext.h
	sources/contexts/gameStarting/initWindowAndRenderer/initWindowRenderer.h
	sources/contexts/gameStarting/initPrefPath/initPrefPath.h
	sources/contexts/gameStarting/mainMenu/mainMenu.h
	sources/contexts/gameStarting/mainMenu/mainMenuWidgets.h
	sources/contexts/gameStarting/setupFiles/setupLanguageFile.h
	sources/contexts/gameStarting/setupFiles/setupConfigFiles.h
	sources/contexts/gameStarting/setupFiles/createConfigFiles.h
	sources/contexts/gameStarting/initSDL2/sdl2_initialization.h
	sources/contexts/credits/creditsContext.h
	sources/contexts/credits/creditsMenuData.h
	sources/contexts/onePlayerGame/inGameMainMenu/race/raceMainMenuContext.h
	sources/contexts/onePlayerGame/inGameMainMenu/race/raceMainMenuGraphicalInterface.h
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceGraphicalInterface.h
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceContext.h
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/consts.h
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/raceLevelsCount.h
	sources/contexts/onePlayerGame/campaignEnd/campaignEndContext.h
	sources/contexts/onePlayerGame/campaignEnd/campEndInterface.h
	sources/contexts/onePlayerGame/bestScoresMenu/mainInterface.h
	sources/contexts/onePlayerGame/bestScoresMenu/bestScoresData.h
	sources/contexts/onePlayerGame/bestScoresMenu/bestScoresContext.h
	sources/contexts/onePlayerGame/demoLoading/demoLoadingInterface.h
	sources/contexts/onePlayerGame/demoLoading/demoLoadingContext.h
	sources/contexts/onePlayerGame/demoLoading/demoFilesDisplayer.h
	sources/contexts/onePlayerGame/newGame/newGameInterface.h
	sources/contexts/onePlayerGame/newGame/newGameContext.h
	sources/contexts/onePlayerGame/demoRecording/demoRecordingInterface.h
	sources/contexts/onePlayerGame/demoRecording/bonusesBagAndCoinEditBoxes.h
	sources/contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileContext.h
	sources/contexts/onePlayerGame/demoRecording/writeDemoFile/getTemplatedString.h
	sources/contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileInterface.h
	sources/contexts/onePlayerGame/demoRecording/levelSelectionInterface.h
	sources/contexts/onePlayerGame/demoRecording/levelSelectionButtons.h
	sources/contexts/onePlayerGame/demoRecording/demoRecordingContext.h
	sources/contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceGraphicalInterface.h
	sources/contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceContext.h
	sources/contexts/onePlayerGame/loadGame/gameLoadContext.h
)

set( SOURCES
	sources/main.cpp
	sources/contexts/options/optionsContext.cpp
	sources/contexts/options/graphics/graphicsContext.cpp
	sources/contexts/options/graphics/graphicsMenuData.cpp
	sources/contexts/options/audio/volumeBar.cpp
	sources/contexts/options/audio/audioPanel.cpp
	sources/contexts/options/audio/musicConfig.cpp
	sources/contexts/options/audio/soundConfig.cpp
	sources/contexts/options/audio/audioContext.cpp
	sources/contexts/options/mainMenuData.cpp
	sources/contexts/options/languages/languageContext.cpp
	sources/contexts/options/languages/languagesMenuGraphics.cpp
	sources/contexts/gameStarting/startMiniScreen/startMiniScreenContext.cpp
	sources/contexts/gameStarting/initWindowAndRenderer/initWindowRenderer.cpp
	sources/contexts/gameStarting/initPrefPath/initPrefPath.cpp
	sources/contexts/gameStarting/mainMenu/mainMenu.cpp
	sources/contexts/gameStarting/mainMenu/mainMenuWidgets.cpp
	sources/contexts/gameStarting/setupFiles/setupConfigFiles.cpp
	sources/contexts/gameStarting/setupFiles/createConfigFiles.cpp
	sources/contexts/gameStarting/setupFiles/setupLanguageFile.cpp
	sources/contexts/gameStarting/initSDL2/sdl2_initialization.cpp
	sources/contexts/credits/creditsContext.cpp
	sources/contexts/credits/creditsMenuData.cpp
	sources/contexts/onePlayerGame/inGameMainMenu/race/raceMainMenuContext.cpp
	sources/contexts/onePlayerGame/inGameMainMenu/race/raceMainMenuGraphicalInterface.cpp
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceContext.cpp
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/raceLevelsCount.cpp
	sources/contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceGraphicalInterface.cpp
	sources/contexts/onePlayerGame/campaignEnd/campaignEndContext.cpp
	sources/contexts/onePlayerGame/campaignEnd/campEndInterface.cpp
	sources/contexts/onePlayerGame/bestScoresMenu/bestScoresData.cpp
	sources/contexts/onePlayerGame/bestScoresMenu/bestScoresContext.cpp
	sources/contexts/onePlayerGame/bestScoresMenu/mainInterface.cpp
	sources/contexts/onePlayerGame/demoLoading/demoLoadingContext.cpp
	sources/contexts/onePlayerGame/demoLoading/demoLoadingInterface.cpp
	sources/contexts/onePlayerGame/demoLoading/demoFilesDisplayer.cpp
	sources/contexts/onePlayerGame/newGame/newGameInterface.cpp
	sources/contexts/onePlayerGame/newGame/newGameContext.cpp
	sources/contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileContext.cpp
	sources/contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileInterface.cpp
	sources/contexts/onePlayerGame/demoRecording/levelSelectionButtons.cpp
	sources/contexts/onePlayerGame/demoRecording/demoRecordingInterface.cpp
	sources/contexts/onePlayerGame/demoRecording/levelSelectionInterface.cpp
	sources/contexts/onePlayerGame/demoRecording/demoRecordingContext.cpp
	sources/contexts/onePlayerGame/demoRecording/bonusesBagAndCoinEditBoxes.cpp
	sources/contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceContext.cpp
	sources/contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceGraphicalInterface.cpp
	sources/contexts/onePlayerGame/loadGame/gameLoadContext.cpp
)

add_executable(	
	${PROJECT_NAME} 
	WIN32
	${SOURCES} 
	${HEADERS} 
	${INC_DIRS}
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
	PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
	PRIVATE ${SDL2_MIXER_INCLUDE_DIRS}
	PRIVATE sources
	PRIVATE ../../libraries/genericLib/sources
	PRIVATE ../../libraries/spriteMoveLib/sources
	PRIVATE ../../libraries/sdl2_wrapper/sources
	PRIVATE ../../libraries/sdlLogoDisplay/sources
	PRIVATE ../../libraries/commonFiles/sources
	PRIVATE ../../libraries/demosLibrary/sources
	PRIVATE ../../libraries/gameSaveAndLoad/sources
	PRIVATE ../../libraries/consts/sources
	PRIVATE ../../libraries/gameCommon/sources
	PRIVATE ../../libraries/onePlayerInGame/sources
	PRIVATE ../../libraries/duelsGame/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE onePlayerInGame
	PRIVATE duelsGame
	PRIVATE demosLibrary
	PRIVATE commonFiles
	PRIVATE gameSaveAndLoad
	PRIVATE gameCommon
	PRIVATE soundSystem
	PRIVATE sdlLogoDisplay
	PRIVATE sdl2_wrapper
	PRIVATE genericLib
	PRIVATE spriteMoveLib
	PRIVATE ${SDL2_LIBRARIES} 
	PRIVATE ${SDL2_IMAGE_LIBRARIES} 
	PRIVATE ${SDL2_TTF_LIBRARIES} 
	PRIVATE ${SDL2_MIXER_LIBRARIES}
)

set_target_properties(
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS NO 
	LINKER_LANGUAGE CXX
)
