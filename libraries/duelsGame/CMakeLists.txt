cmake_minimum_required(VERSION 3.13)

project( duelsGame LANGUAGES CXX )

set( HEADERS
	sources/duels/instructions/elementsCollisions.h
	sources/duels/instructions/activateBonuses.h
	sources/duels/setFinalAchievement/contextWidgets.h
	sources/duels/setFinalAchievement/finalAchievementContext.h
	sources/duels/matchConfig/graphics/zoneChoiceGraphics.h
	sources/duels/matchConfig/graphics/zonesPanels.h
	sources/duels/matchConfig/graphics/bonusVignettes.h
	sources/duels/matchConfig/graphics/spinAnimation.h
	sources/duels/matchConfig/bonusesSlots/bonusInterface.h
	sources/duels/matchConfig/bonusesSlots/bonusSlot.h
	sources/duels/matchConfig/bonusesSlots/slotsData.h
	sources/duels/matchConfig/bonusesSlots/bonusesSlotsContext.h
	sources/duels/matchConfig/bonusesSlots/slotsConsts.h
	sources/duels/matchConfig/zoneSpecificOptions/halloween/elements.h
	sources/duels/matchConfig/zoneSpecificOptions/halloween/halloweenSpecific.h
	sources/duels/matchConfig/zoneSpecificOptions/halloween/languageTexts.h
	sources/duels/matchConfig/textFilesLoading/fromStringsToTextures.h
	sources/duels/matchConfig/interface/helpTexts.h
	sources/duels/matchConfig/interface/zoneChoiceThings.h
	sources/duels/matchConfig/interface/bonusEditBoxes.h
	sources/duels/matchConfig/interface/othersOptions.h
	sources/duels/matchConfig/matchConfigContext.h
	sources/duels/matchConfig/zoneChoice/zoneChoiceContext.h
	sources/duels/matchConfig/zoneChoice/zonesChoicePanels.h
	sources/duels/inGameObjects/playerInputs/loadInputConfig.h
	sources/duels/inGameObjects/playerInputs/inputsTypes.h
	sources/duels/inGameObjects/playerInputs/inputsConsts.h
	sources/duels/inGameObjects/playerInputs/playersInputs.h
	sources/duels/inGameObjects/gameElements/duelsLevelOptions.h
	sources/duels/inGameObjects/gameElements/spawnsData.h
	sources/duels/inGameObjects/gameElements/collisionsInfos.h
	sources/duels/inGameObjects/gameElements/collisionBools.h
	sources/duels/inGameObjects/rackets/racket.h
	sources/duels/inGameObjects/global/playersThings.h
	sources/duels/inGameObjects/global/duelsGlobalObject.h
	sources/duels/inGameObjects/bonusCoins/coinsMain.h
	sources/duels/inGameObjects/bonusCoins/bonusCoin.h
	sources/duels/inGameObjects/balls/ballsMain.h
	sources/duels/inGameObjects/balls/duelBall.h
	sources/duels/inGameObjects/bonus/bonusPicker.h
	sources/duels/inGameObjects/bonus/bonusDrawer.h
	sources/duels/inGameObjects/bonus/bonusGenerator.h
	sources/duels/inGameObjects/bonus/bonusStateMachine.h
	sources/duels/inGameObjects/playerScore/playerScoreDrawing.h
	sources/duels/championshipEnd/champEndContext.h
	sources/duels/championshipEnd/matchEndInterface.h
	sources/duels/championshipEnd/graphicInterface.h
	sources/duels/zones/allZonesConfig.h
	sources/duels/zones/halloween/halloweenContext.h
	sources/duels/zones/halloween/subObjects/potBubbles/bubblesDrawer.h
	sources/duels/zones/halloween/subObjects/halloweenArea.h
	sources/duels/zones/halloween/subObjects/pumpkins/playersSpecialPumpkins.h
	sources/duels/zones/halloween/subObjects/pumpkins/pumpkinFactory.h
	sources/duels/zones/halloween/subObjects/pumpkins/collisionsWithPlayerRacket.h
	sources/duels/zones/halloween/subObjects/halloweenConfig.h
	sources/duels/zones/halloween/subObjects/halloweenGlobalObject.h
	sources/duels/zones/halloween/subObjects/halloweenFactory.h
	sources/duels/zones/simpleZone/simpleZoneArea.h
	sources/duels/zones/simpleZone/simpleZoneContext.h
	sources/duels/zones/metalStrings/subObjects/barriersData.h
	sources/duels/zones/metalStrings/subObjects/metalStringsConfig.h
	sources/duels/zones/metalStrings/subObjects/switchsData.h
	sources/duels/zones/metalStrings/subObjects/stringDrawer.h
	sources/duels/zones/metalStrings/subObjects/notStringsElements.h
	sources/duels/zones/metalStrings/subObjects/steamPipe.h
	sources/duels/zones/metalStrings/subObjects/globalSpecificObject.h
	sources/duels/zones/metalStrings/subObjects/consts.h
	sources/duels/zones/metalStrings/subObjects/metalStringsData.h
	sources/duels/zones/metalStrings/subObjects/verticalBarriersDrawing.h
	sources/duels/zones/metalStrings/metalStringsContext.h
	sources/duels/controls/makeInpStringFromData.h
	sources/duels/controls/objects/screenGraphics.h
	sources/duels/controls/objects/mainObject.h
	sources/duels/controls/objects/joystickInfosGraphics.h
	sources/duels/controls/objects/playerDataGraphics.h
	sources/duels/controls/objects/joysticksInfosDrawer.h
	sources/duels/controls/inputConfigContext.h
	sources/duels/controls/inputScreenConsts.h
)

set( SOURCES
	sources/duels/instructions/elementsCollisions.cpp
	sources/duels/instructions/activateBonuses.cpp
	sources/duels/setFinalAchievement/contextWidgets.cpp
	sources/duels/setFinalAchievement/finalAchivementContext.cpp
	sources/duels/matchConfig/graphics/zonesPanels.cpp
	sources/duels/matchConfig/graphics/spinAnimation.cpp
	sources/duels/matchConfig/graphics/bonusVignettes.cpp
	sources/duels/matchConfig/graphics/zoneChoiceGraphics.cpp
	sources/duels/matchConfig/matchConfigContext.cpp
	sources/duels/matchConfig/bonusesSlots/bonusSlot.cpp
	sources/duels/matchConfig/bonusesSlots/bonusesSlotsContext.cpp
	sources/duels/matchConfig/bonusesSlots/slotsData.cpp
	sources/duels/matchConfig/bonusesSlots/bonusInterface.cpp
	sources/duels/matchConfig/zoneSpecificOptions/halloween/elements.cpp
	sources/duels/matchConfig/zoneSpecificOptions/halloween/halloweenSpecific.cpp
	sources/duels/matchConfig/textFilesLoading/fromStringsToTextures.cpp
	sources/duels/matchConfig/interface/othersOptions.cpp
	sources/duels/matchConfig/interface/helpTexts.cpp
	sources/duels/matchConfig/interface/zoneChoiceThings.cpp
	sources/duels/matchConfig/interface/bonusEditBoxes.cpp
	sources/duels/matchConfig/zoneChoice/zonesChoicePanels.cpp
	sources/duels/matchConfig/zoneChoice/zoneChoiceContext.cpp
	sources/duels/inGameObjects/playerInputs/loadInputConfig.cpp
	sources/duels/inGameObjects/playerInputs/playersInputs.cpp
	sources/duels/inGameObjects/playerInputs/inputsTypes.cpp
	sources/duels/inGameObjects/gameElements/spawnsData.cpp
	sources/duels/inGameObjects/gameElements/collisionBools.cpp
	sources/duels/inGameObjects/gameElements/duelsLevelOptions.cpp
	sources/duels/inGameObjects/gameElements/collisionsInfos.cpp
	sources/duels/inGameObjects/rackets/racket.cpp
	sources/duels/inGameObjects/global/playersThings.cpp
	sources/duels/inGameObjects/global/duelsGlobalObject.cpp
	sources/duels/inGameObjects/bonusCoins/bonusCoin.cpp
	sources/duels/inGameObjects/bonusCoins/coinsMain.cpp
	sources/duels/inGameObjects/balls/duelBall.cpp
	sources/duels/inGameObjects/balls/ballsMain.cpp
	sources/duels/inGameObjects/bonus/bonusDrawer.cpp
	sources/duels/inGameObjects/bonus/bonusPicker.cpp
	sources/duels/inGameObjects/bonus/bonusGenerator.cpp
	sources/duels/inGameObjects/bonus/bonusStateMachine.cpp
	sources/duels/inGameObjects/playerScore/playerScoreDrawing.cpp
	sources/duels/championshipEnd/champEndContext.cpp
	sources/duels/championshipEnd/graphicInterface.cpp
	sources/duels/championshipEnd/matchEndInterface.cpp
	sources/duels/zones/allZonesConfig.cpp
	sources/duels/zones/halloween/halloweenContext.cpp
	sources/duels/zones/halloween/subObjects/potBubbles/bubblesDrawer.cpp
	sources/duels/zones/halloween/subObjects/halloweenGlobalObject.cpp
	sources/duels/zones/halloween/subObjects/halloweenConfig.cpp
	sources/duels/zones/halloween/subObjects/pumpkins/collisionsWithPlayerRacket.cpp
	sources/duels/zones/halloween/subObjects/pumpkins/playersSpecialPumpkins.cpp
	sources/duels/zones/halloween/subObjects/pumpkins/pumpkinFactory.cpp
	sources/duels/zones/halloween/subObjects/halloweenArea.cpp
	sources/duels/zones/halloween/subObjects/halloweenFactory.cpp
	sources/duels/zones/simpleZone/simpleZoneContext.cpp
	sources/duels/zones/simpleZone/simpleZoneArea.cpp
	sources/duels/zones/metalStrings/subObjects/barriersData.cpp
	sources/duels/zones/metalStrings/subObjects/steamPipe.cpp
	sources/duels/zones/metalStrings/subObjects/verticalBarriersDrawing.cpp
	sources/duels/zones/metalStrings/subObjects/switchsData.cpp
	sources/duels/zones/metalStrings/subObjects/stringDrawer.cpp
	sources/duels/zones/metalStrings/subObjects/metalStringsData.cpp
	sources/duels/zones/metalStrings/subObjects/metalStringsConfig.cpp
	sources/duels/zones/metalStrings/subObjects/globalSpecificObject.cpp
	sources/duels/zones/metalStrings/subObjects/notStringsElements.cpp
	sources/duels/zones/metalStrings/metalStringsContext.cpp
	sources/duels/controls/objects/joysticksInfosDrawer.cpp
	sources/duels/controls/objects/joystickInfosGraphics.cpp
	sources/duels/controls/objects/playerDataGraphics.cpp
	sources/duels/controls/objects/mainObject.cpp
	sources/duels/controls/objects/screenGraphics.cpp
	sources/duels/controls/makeInpStringFromData.cpp
	sources/duels/controls/inputConfigContext.cpp
)

add_library(	
	${PROJECT_NAME} 
	STATIC
	${SOURCES} 
	${HEADERS} 
	${INC_DIRS}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
	PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
	PRIVATE ${SDL2_MIXER_INCLUDE_DIRS}
	PRIVATE sources
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/genericLib
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/sdl2_wrapper
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/spriteMoveLib
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/soundSystem
	PRIVATE ../consts/sources
	PRIVATE ../commonFiles/sources
	PRIVATE ../gameSaveAndLoad/sources
	PRIVATE ../gameCommon/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE gameCommon
	PRIVATE commonFiles
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
