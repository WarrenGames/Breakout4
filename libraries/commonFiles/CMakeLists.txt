cmake_minimum_required(VERSION 3.13)

project( commonFiles LANGUAGES CXX )

set( HEADERS
	sources/appStart/miniScreenGui.h
	sources/appStart/miniScreenConsts.h
	sources/generic/gameSoundSystem/soundsFileDataPaths.h
	sources/generic/gameSoundSystem/gameSoundSystem.h
	sources/generic/fileSystem/fileProcessing/pathMakers.h
	sources/generic/fileSystem/fileProcessing/templateLogging.h
	sources/generic/fileSystem/fileProcessing/filesNames.h
	sources/generic/display/loadDrawFrequencyModule.h
	sources/generic/texturing/backgroundDrawer.h
	sources/generic/input/userInput.h
	sources/generic/maths/orientation.h
	sources/options/joystickInterface/joystickInfosInterface.h
	sources/options/joystickInterface/joystickGraphicsValues.h
	sources/types/brickData.h
	sources/types/essentialsStruct.h
	sources/types/pi.h
	sources/types/spriteSize.h
	sources/consts/fontsConsts.h
	sources/consts/constexprScreen.h
	sources/consts/constPaths.h
	sources/consts/squareSize.h
	sources/consts/sdlColors.h
	sources/consts/sdlMixerConsts.h
	sources/consts/gridOffsetCoord.h
	sources/onePlayerGame/level/textures/bricksTexturesDrawer.h
	sources/onePlayerGame/level/textures/bricksTexturesLoader.h
	sources/onePlayerGame/level/data/gridProcessing/processGridValue.h
)

set( SOURCES
	sources/appStart/miniScreenGui.cpp
	sources/generic/gameSoundSystem/soundsFileDataPaths.cpp
	sources/generic/gameSoundSystem/gameSoundSystem.cpp
	sources/generic/fileSystem/fileProcessing/pathMakers.cpp
	sources/generic/display/loadDrawFrequencyModule.cpp
	sources/generic/texturing/backgroundDrawer.cpp
	sources/generic/input/userInput.cpp
	sources/generic/maths/orientation.cpp
	sources/options/joystickInterface/joystickInfosInterface.cpp
	sources/options/joystickInterface/joystickGraphicsValues.cpp
	sources/types/essentialsStruct.cpp
	sources/types/spriteSize.cpp
	sources/types/brickData.cpp
	sources/onePlayerGame/level/textures/bricksTexturesLoader.cpp
	sources/onePlayerGame/level/textures/bricksTexturesDrawer.cpp
	sources/onePlayerGame/level/data/gridProcessing/processGridValue.cpp
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
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/genericLib
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/sdl2_wrapper
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/soundSystem
	PRIVATE ../consts/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE soundSystem
	PRIVATE sdl2_wrapper
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
