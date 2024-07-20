cmake_minimum_required(VERSION 3.13)

project( Breakout4 LANGUAGES CXX )

#If you don't need wxWidgets framework set the boolean below to OFF ('ON' else).
#The games like 'Bob the blob' or 'SDL2_WarrenTetris' don't need wxWidgets framework at all.
#In 'Breakout4' game you can choose if you don't want to use wxWidgets, but you won't build wxSavesEditor and wxLevelEditor.
set( USE_WX_WIDGETS_FRAMEWORK ON )

if( DEFINED SQUARE_SIZE )
	file( WRITE "libraries/commonFiles/sources/consts/squareSize.h" "constexpr int SQR_SIZE = ${SQUARE_SIZE};" )
	message( WARNING "You defined the SQUARE_SIZE value as: ${SQUARE_SIZE}" )
else()
	file( WRITE "libraries/commonFiles/sources/consts/squareSize.h" "constexpr int SQR_SIZE = 64;" )
	message( WARNING "SQUARE_SIZE value is set to default: 64" )
	set( SQUARE_SIZE 64 )
endif()

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)

#set this path to the built WarrenGamesCustomLibs libraries directory (needed below at line 51) (use a canonical path, not a relative one)
set( WARREN_LIBS_BUILDING_PATH "/media/antoine/projetsLinux/temp/CmakeAndWxWidgetsOption/builtWarrenCustomLibs" )

set( WARREN_STATIC_LIBS_DIR "builtArchives" )
set( WARREN_LIBS_INCLUDES_PATH "${WARREN_LIBS_BUILDING_PATH}/includes" )
set( WARREN_LIBS_STATIC_LIBS_PATH "${WARREN_LIBS_BUILDING_PATH}/${WARREN_STATIC_LIBS_DIR}" )

if(WIN32)
    set( SDL2_DIR "" )
    if( USE_WX_WIDGETS_FRAMEWORK )
		set( wxWidgets_ROOT_DIR "" )
		set( wxWidgets_INCLUDE_DIRS "" )
		set( wxWidgets_LIB_DIR "" )
	endif()
endif(WIN32)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

link_directories( ${WARREN_LIBS_STATIC_LIBS_PATH} )

if( USE_WX_WIDGETS_FRAMEWORK )
	set( wxWidgets_CONFIGURATION mswu )
	find_package( wxWidgets COMPONENTS core base REQUIRED )
	add_subdirectory(executables/wxLevelEditor)
	add_subdirectory(executables/wxSavesEditor)
endif()

add_subdirectory(executables/game)
add_subdirectory(libraries/commonFiles)
add_subdirectory(libraries/consts)
add_subdirectory(libraries/demosLibrary)
add_subdirectory(libraries/duelsGame)
add_subdirectory(libraries/gameCommon)
add_subdirectory(libraries/gameSaveAndLoad)
add_subdirectory(libraries/onePlayerInGame)

if(UNIX)
	include(GNUInstallDirs)
	install( 
		TARGETS 
			game 
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
	)
else()
	install( 
		TARGETS 
			game 
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT Runtime
	)
endif(UNIX)

if( USE_WX_WIDGETS_FRAMEWORK )
	if(UNIX)
		include(GNUInstallDirs)
		install( 
			TARGETS
				wxLevelEditor 
				wxSavesEditor 
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
		)
	else()
		install( 
			TARGETS
				wxLevelEditor 
				wxSavesEditor 
			RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT Runtime
		)
	endif(UNIX)
endif()