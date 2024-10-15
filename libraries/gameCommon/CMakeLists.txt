cmake_minimum_required(VERSION 3.13)

project( gameCommon LANGUAGES CXX )

set( HEADERS
	sources/pausedTimesCounter/pausedTimesCounter.h
	sources/hellSkulls/skullDrawer.h
	sources/hellSkulls/skullData.h
	sources/hellSkulls/skullConsts.h
	sources/rackets/racketData.h
	sources/rackets/racketDrawer.h
	sources/time/intervalAndRandomTimeHappening.h
	sources/steamData/steamSample.h
	sources/fireBall/fireBallConsts.h
	sources/fireBall/fireBallDrawer.h
	sources/fireBall/fireBallDrawData.h
	sources/stalactites/racketFreezesDurationsLoader.h
	sources/stalactites/stalactitesConsts.h
	sources/stalactites/stalactitesDrawer.h
	sources/stalactites/onePlayerStalactiteData.h
	sources/stalactites/stalactitesData.h
	sources/pinguins/pinguinConsts.h
	sources/pinguins/pinguinDrawData.h
	sources/cheating/checkCheatingFile.h
	sources/rectCollisions/processBouncing.h
	sources/rectCollisions/monsterCollisionsWithRect.h
	sources/rectCollisions/colObjMvCenterAndPosWithColRect.h
	sources/rectCollisions/positionCheck.h
	sources/rectCollisions/objMoveWithRectCollisions.h
	sources/rectCollisions/rectLoader.h
	sources/rectCollisions/activeWithStaticObjectCollision.h
	sources/rectCollisions/brickGridCollisions.h
	sources/rectCollisions/objMoveWRectCollide.h
	sources/pathsAndRects/pathZoneRects.h
	sources/pathsAndRects/pathNodes.h
	sources/halloween/pumpkins/pumpkinDrawer.h
	sources/halloween/pumpkins/pumpkinConsts.h
	sources/halloween/pumpkins/pumpkinCombo.h
	sources/halloween/bat/batConsts.h
	sources/halloween/bat/badBatDrawer.h
	sources/halloween/bat/batFactory.h
	sources/halloween/bat/badBatData.h
	sources/explosions/allExplosions.h
	sources/explosions/entityExplosion.h
	sources/explosions/explosionLoader.h
)

set( SOURCES
	sources/pausedTimesCounter/pausedTimesCounter.cpp
	sources/hellSkulls/skullData.cpp
	sources/hellSkulls/skullDrawer.cpp
	sources/rackets/racketDrawer.cpp
	sources/rackets/racketData.cpp
	sources/time/intervalAndRandomTimeHappening.cpp
	sources/steamData/steamSample.cpp
	sources/fireBall/fireBallDrawData.cpp
	sources/fireBall/fireBallDrawer.cpp
	sources/stalactites/stalactitesData.cpp
	sources/stalactites/racketFreezesDurationsLoader.cpp
	sources/stalactites/stalactitesDrawer.cpp
	sources/stalactites/onePlayerStalactiteData.cpp
	sources/pinguins/pinguinDrawData.cpp
	sources/cheating/checkCheatingFile.cpp
	sources/rectCollisions/objMoveWRectCollide.cpp
	sources/rectCollisions/activeWithStaticObjectCollision.cpp
	sources/rectCollisions/brickGridCollisions.cpp
	sources/rectCollisions/rectLoader.cpp
	sources/rectCollisions/colObjMvCenterAndPosWithColRect.cpp
	sources/rectCollisions/processBouncing.cpp
	sources/rectCollisions/positionCheck.cpp
	sources/rectCollisions/objMoveWithRectCollisions.cpp
	sources/rectCollisions/monsterCollisionsWithRect.cpp
	sources/pathsAndRects/pathZoneRects.cpp
	sources/pathsAndRects/pathNodes.cpp
	sources/halloween/pumpkins/pumpkinCombo.cpp
	sources/halloween/pumpkins/pumpkinDrawer.cpp
	sources/halloween/bat/badBatDrawer.cpp
	sources/halloween/bat/badBatData.cpp
	sources/halloween/bat/batFactory.cpp
	sources/explosions/explosionLoader.cpp
	sources/explosions/entityExplosion.cpp
	sources/explosions/allExplosions.cpp
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
)

target_link_libraries(	
	${PROJECT_NAME}
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
