cmake_minimum_required(VERSION 3.8)

project( Breakout4 LANGUAGES CXX )

if( DEFINED SQUARE_SIZE )
	file( WRITE "libs/commonFiles/sources/consts/squareSize.h" "constexpr int SQR_SIZE = ${SQUARE_SIZE};" )
	message( WARNING "You defined the SQUARE_SIZE value as: ${SQUARE_SIZE}" )
else()
	file( WRITE "libs/commonFiles/sources/consts/squareSize.h" "constexpr int SQR_SIZE = 64;" )
	message( WARNING "SQUARE_SIZE value is set to default: 64" )
	set( SQUARE_SIZE 64 )
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmakeModules)

if( UNIX )
	include(GNUInstallDirs)
endif( UNIX )

if(WIN32)
    set( SDL2_DIR "" )
    set( wxWidgets_ROOT_DIR "" )
    set( wxWidgets_INCLUDE_DIRS "" )
    set( wxWidgets_LIB_DIR "" )
endif(WIN32)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


set( wxWidgets_CONFIGURATION mswu )
find_package( wxWidgets COMPONENTS core base REQUIRED )

add_subdirectory(executables/game)
add_subdirectory(executables/wxLevelEditor)
add_subdirectory(executables/wxSavesEditor)
add_subdirectory(libs/genericLib)
add_subdirectory(libs/spriteMoveLib)
add_subdirectory(libs/sdl2_wrapper)
add_subdirectory(libs/gameSaveAndLoad)
add_subdirectory(libs/commonFiles)
add_subdirectory(libs/consts)
add_subdirectory(libs/wxPrefPath)