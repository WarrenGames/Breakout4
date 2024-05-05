cmake_minimum_required(VERSION 3.13)

project( soundSystem LANGUAGES CXX )

if(UNIX)
	include(GNUInstallDirs)
endif(UNIX)

set(HEADERS
	sources/soundSystem/soundSystem.h
	sources/soundSystem/soundChannelsSystem.h
	sources/soundSystem/soundsListLoader.h
	sources/soundSystem/soundsVolume.h
	sources/soundSystem/soundsPathsConsts.h
	sources/soundSystem/soundsPlayer.h
)

set(SOURCES
	sources/soundSystem/soundsPlayer.cpp
	sources/soundSystem/soundChannelsSystem.cpp
	sources/soundSystem/soundSystem.cpp
	sources/soundSystem/soundsListLoader.cpp
	sources/soundSystem/soundsVolume.cpp
)

add_library(
	${PROJECT_NAME} 
	STATIC
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
	PRIVATE ../genericLib/sources
	PRIVATE ../sdl2_wrapper/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE genericLib
	PRIVATE sdl2_wrapper
)

set_target_properties(	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20 
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS ON 
	LINKER_LANGUAGE CXX
)
