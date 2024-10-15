cmake_minimum_required(VERSION 3.13)

project( onePlayerInGame LANGUAGES CXX )

set( HEADERS
	sources/demosLoadingAndSaving/moveStacks/moveDemosStacks.h
	sources/demosLoadingAndSaving/saving/saveDemoFile.h
	sources/demosLoadingAndSaving/loading/loadDemoFile.h
	sources/demosLoadingAndSaving/loading/stackSquareSizeLegacy.h
	sources/levelEnd/levelEndContext.h
	sources/levelEnd/completeLevelInterface.h
	sources/gamePaused/gameInPause.h
	sources/gamePaused/gamePausedGUI.h
	sources/seeNextLevel/seeNextLevelContext.h
	sources/levelComponents/traceCross/traceCross.h
	sources/levelComponents/global/monstersTriggers.h
	sources/levelComponents/global/globalGameObject.h
	sources/levelComponents/bonusCoins/coinSample.h
	sources/levelComponents/freeFunctions/ballWithGridCollisions.h
	sources/levelComponents/freeFunctions/testBallPositionWithGrid.h
	sources/levelComponents/freeFunctions/withSkullBrickBallCollision.h
	sources/levelComponents/freeFunctions/detectLevelEnd.h
	sources/levelComponents/freeFunctions/ballWithPinguinBrickCollisions.h
	sources/levelComponents/fallingBonuses/fallingBonuses.h
	sources/levelComponents/onePlayerRacket/onePlayerRacket.h
	sources/levelComponents/demosObjects/antarcticDemoPackage.h
	sources/levelComponents/demosObjects/playerStartingData.h
	sources/levelComponents/demosObjects/demoMainPackage.h
	sources/levelComponents/antarcticEpisodeThings/antarcticPackage.h
	sources/levelComponents/antarcticEpisodeThings/stalactites/iceStalactites.h
	sources/levelComponents/antarcticEpisodeThings/stalactites/onePlayerStalactitesLoading.h
	sources/levelComponents/antarcticEpisodeThings/onePlayerPinguins/pinguinsDataLoader.h
	sources/levelComponents/antarcticEpisodeThings/onePlayerPinguins/onePlayerPinguin.h
	sources/levelComponents/rims/rimsPast.h
	sources/levelComponents/rims/rimsScoreValueDrawing.h
	sources/levelComponents/rims/playerRims.h
	sources/levelComponents/rims/rimsScoreStock.h
	sources/levelComponents/rims/rimsGlobal.h
	sources/levelComponents/hellEpisodeThings/hellSkulls/hellSkullGlobal.h
	sources/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullElement.h
	sources/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullPack.h
	sources/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullActivity.h
	sources/levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.h
	sources/levelComponents/hellEpisodeThings/hellSkulls/configuration/hellSkullDataLoader.h
	sources/levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h
	sources/levelComponents/hellEpisodeThings/fireBalls/fireBallGlobal.h
	sources/levelComponents/hellEpisodeThings/fireBalls/inGame/bottomScreenFireBallsPack.h
	sources/levelComponents/hellEpisodeThings/fireBalls/inGame/fireBallElement.h
	sources/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.h
	sources/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallFileData.h
	sources/levelComponents/hellEpisodeThings/hellPackage.h
	sources/levelComponents/infoBar/infoBar.h
	sources/levelComponents/infoBar/playedTimeCounter.h
	sources/levelComponents/balls/ballsThings.h
	sources/levelComponents/balls/ballSpeedsOptions.h
	sources/levelComponents/monsters/pinguinBehaviorData.h
	sources/levelComponents/inGameBagThings/bonusesCountGraphics.h
	sources/levelComponents/inGameBagThings/iconsPositionsLoader.h
	sources/levelComponents/inGameBagThings/bagObject.h
	sources/levelComponents/inGameBagThings/bagViewContext.h
	sources/levelComponents/inputs/joystickData.h
	sources/levelComponents/inputs/levelControls.h
	sources/levelComponents/inputs/playerActions.h
	sources/levelComponents/inputs/userInputs.h
	sources/levelComponents/inputs/customInputsData.h
	sources/levelComponents/inputs/joystickInputData.h
	sources/inputConfig/inputConfigContext.h
	sources/inputConfig/staticGraphics.h
	sources/inputConfig/inputThings.h
	sources/saveAndLoad/common/slotGraphics.h
	sources/saveAndLoad/common/slotsUserInterface.h
	sources/saveAndLoad/gameSaving/saveGameContext.h
	sources/levelsContexts/stdLevelContext.h
	sources/levelsContexts/antarcticContext.h
	sources/levelsContexts/hellContext.h
	sources/bonusesShop/shopInterface.h
	sources/bonusesShop/shopContext.h
)

set( SOURCES
	sources/demosLoadingAndSaving/moveStacks/moveDemosStacks.cpp
	sources/demosLoadingAndSaving/saving/saveDemoFile.cpp
	sources/demosLoadingAndSaving/loading/stackSquareSizeLegacy.cpp
	sources/demosLoadingAndSaving/loading/loadDemoFile.cpp
	sources/levelEnd/completeLevelInterface.cpp
	sources/levelEnd/levelEndContext.cpp
	sources/gamePaused/gamePausedGUI.cpp
	sources/gamePaused/gameInPause.cpp
	sources/seeNextLevel/seeNextLevelContext.cpp
	sources/levelComponents/traceCross/traceCross.cpp
	sources/levelComponents/global/monstersTriggers.cpp
	sources/levelComponents/global/globalGameObject.cpp
	sources/levelComponents/bonusCoins/coinSample.cpp
	sources/levelComponents/freeFunctions/ballWithPinguinBrickCollisions.cpp
	sources/levelComponents/freeFunctions/testBallPositionWithGrid.cpp
	sources/levelComponents/freeFunctions/ballWithGridCollisions.cpp
	sources/levelComponents/freeFunctions/withSkullBrickBallCollision.cpp
	sources/levelComponents/freeFunctions/detectLevelEnd.cpp
	sources/levelComponents/fallingBonuses/fallingBonuses.cpp
	sources/levelComponents/onePlayerRacket/onePlayerRacket.cpp
	sources/levelComponents/demosObjects/demoMainPackage.cpp
	sources/levelComponents/demosObjects/playerStartingData.cpp
	sources/levelComponents/demosObjects/antarcticDemoPackage.cpp
	sources/levelComponents/antarcticEpisodeThings/antarcticPackage.cpp
	sources/levelComponents/antarcticEpisodeThings/stalactites/iceStalactites.cpp
	sources/levelComponents/antarcticEpisodeThings/stalactites/onePlayerStalactitesLoading.cpp
	sources/levelComponents/antarcticEpisodeThings/onePlayerPinguins/onePlayerPinguin.cpp
	sources/levelComponents/antarcticEpisodeThings/onePlayerPinguins/pinguinsDataLoader.cpp
	sources/levelComponents/rims/playerRims.cpp
	sources/levelComponents/rims/rimsScoreStock.cpp
	sources/levelComponents/rims/rimsScoreValueDrawing.cpp
	sources/levelComponents/rims/rimsGlobal.cpp
	sources/levelComponents/rims/rimsPast.cpp
	sources/levelComponents/hellEpisodeThings/hellSkulls/hellSkullGlobal.cpp
	sources/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullElement.cpp
	sources/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullPack.cpp
	sources/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullActivity.cpp
	sources/levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.cpp
	sources/levelComponents/hellEpisodeThings/hellSkulls/configuration/hellSkullDataLoader.cpp
	sources/levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.cpp
	sources/levelComponents/hellEpisodeThings/fireBalls/fireBallGlobal.cpp
	sources/levelComponents/hellEpisodeThings/fireBalls/inGame/bottomScreenFireBallsPack.cpp
	sources/levelComponents/hellEpisodeThings/fireBalls/inGame/fireBallElement.cpp
	sources/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallFileData.cpp
	sources/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.cpp
	sources/levelComponents/hellEpisodeThings/hellPackage.cpp
	sources/levelComponents/infoBar/playedTimeCounter.cpp
	sources/levelComponents/infoBar/infoBar.cpp
	sources/levelComponents/balls/ballSpeedsOptions.cpp
	sources/levelComponents/balls/ballsThings.cpp
	sources/levelComponents/monsters/pinguinBehaviorData.cpp
	sources/levelComponents/inGameBagThings/bagViewContext.cpp
	sources/levelComponents/inGameBagThings/bagObject.cpp
	sources/levelComponents/inGameBagThings/iconsPositionsLoader.cpp
	sources/levelComponents/inGameBagThings/bonusesCountGraphics.cpp
	sources/levelComponents/inputs/playerActions.cpp
	sources/levelComponents/inputs/joystickInputData.cpp
	sources/levelComponents/inputs/joystickData.cpp
	sources/levelComponents/inputs/levelControls.cpp
	sources/levelComponents/inputs/userInputs.cpp
	sources/levelComponents/inputs/customInputsData.cpp
	sources/inputConfig/inputThings.cpp
	sources/inputConfig/staticGraphics.cpp
	sources/inputConfig/inputConfigContext.cpp
	sources/saveAndLoad/common/slotGraphics.cpp
	sources/saveAndLoad/common/slotsUserInterface.cpp
	sources/saveAndLoad/gameSaving/saveGameContext.cpp
	sources/levelsContexts/stdLevelContext.cpp
	sources/levelsContexts/antarcticContext.cpp
	sources/levelsContexts/hellContext.cpp
	sources/bonusesShop/shopContext.cpp
	sources/bonusesShop/shopInterface.cpp
)

add_library(	
	${PROJECT_NAME} 
	STATIC
	${SOURCES} 
	${HEADERS} 
	${INC_DIRS}
)

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
	PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
	PRIVATE ${SDL2_MIXER_INCLUDE_DIRS}
	PRIVATE sources
	PRIVATE ../genericLib/sources
	PRIVATE ../sdl2_wrapper/sources
	PRIVATE ../spriteMoveLib/sources
	PRIVATE ../soundSystem/sources
	PRIVATE ../consts/sources
	PRIVATE ../commonFiles/sources
	PRIVATE ../gameSaveAndLoad/sources
	PRIVATE ../gameCommon/sources
	PRIVATE ../demosLibrary/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE gameCommon
	PRIVATE commonFiles
	PRIVATE gameSaveAndLoad
	PRIVATE demosLibrary
	PRIVATE soundSystem
	PRIVATE sdl2_wrapper
	PRIVATE spriteMoveLib
	PRIVATE genericLib
)

set_target_properties( 	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS NO 
	LINKER_LANGUAGE CXX
)
