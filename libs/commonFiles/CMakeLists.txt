cmake_minimum_required(VERSION 3.0)

project( commonFiles LANGUAGES CXX )

set( HEADERS
		sources/appStart/miniScreenGui.h
		sources/generic/fileSystem/fileProcessing/pathMakers.h
		sources/generic/fileSystem/fileProcessing/templateLogging.h
		sources/generic/fileSystem/fileProcessing/filesNames.h
		sources/generic/display/loadDrawFrequencyModule.h
		sources/generic/texturing/backgroundDrawer.h
		sources/generic/sounds/loadChannelsConfig.h
		sources/generic/sounds/loadGameSounds.h
		sources/generic/sounds/soundStructs.h
		sources/generic/sounds/soundHandler.h
		sources/generic/input/userInput.h
		sources/generic/maths/orientation.h
		sources/types/brickData.h
		sources/types/essentialsStruct.h
		sources/types/pi.h
		sources/types/spriteSize.h
		sources/consts/fontsConsts.h
		sources/consts/constexprScreen.h
		sources/consts/constPaths.h
		sources/consts/sdlColors.h
		sources/consts/sdlMixerConsts.h
		sources/consts/gridOffsetCoord.h
		sources/onePlayerGame/level/textures/bricksTexturesDrawer.h
		sources/onePlayerGame/level/textures/bricksTexturesLoader.h
		sources/onePlayerGame/level/data/gridProcessing/processGridValue.h
)

set( SOURCES
		sources/appStart/miniScreenGui.cpp
		sources/generic/fileSystem/fileProcessing/pathMakers.cpp
		sources/generic/display/loadDrawFrequencyModule.cpp
		sources/generic/texturing/backgroundDrawer.cpp
		sources/generic/sounds/soundHandler.cpp
		sources/generic/sounds/loadGameSounds.cpp
		sources/generic/sounds/loadChannelsConfig.cpp
		sources/generic/sounds/soundStructs.cpp
		sources/generic/input/userInput.cpp
		sources/generic/maths/orientation.cpp
		sources/types/essentialsStruct.cpp
		sources/types/spriteSize.cpp
		sources/types/brickData.cpp
		sources/onePlayerGame/level/textures/bricksTexturesLoader.cpp
		sources/onePlayerGame/level/textures/bricksTexturesDrawer.cpp
		sources/onePlayerGame/level/data/gridProcessing/processGridValue.cpp
)

add_library(	${PROJECT_NAME} 
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
	PRIVATE ../../libs/genericLib/sources
	PRIVATE ../../libs/sdl2_wrapper/sources
	PRIVATE ../../libs/consts/sources
)

target_link_libraries(	${PROJECT_NAME} 
						${SDL2_LIBRARIES} 
						${SDL2_IMAGE_LIBRARIES} 
						${SDL2_TTF_LIBRARIES} 
						${SDL2_MIXER_LIBRARIES}
						genericLib
						sdl2_wrapper
)
						
set_target_properties( 	${PROJECT_NAME} 
						PROPERTIES 
						PUBLIC_HEADER "${HEADERS}" 
						CXX_STANDARD 20
						CXX_STANDARD_REQUIRED YES 
						CXX_EXTENSIONS NO 
						LINKER_LANGUAGE CXX
)
