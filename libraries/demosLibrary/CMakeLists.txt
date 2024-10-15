cmake_minimum_required(VERSION 3.13)

project( demosLibrary LANGUAGES CXX )

set( HEADERS
	sources/demos/objectDirections/objectDirectionData.h
	sources/demos/consts/demosConsts.h
	sources/demos/sounds/soundsStackData.h
	sources/demos/templates/demoStack.h
	sources/demos/inputs/actionData.h
	sources/demos/positions/positionStackData.h
	sources/demos/positions/taggedPositionStackData.h
	sources/demos/objectsDestruction/matrixDemoData.h
	sources/demos/loading/loadDemosVectorsDataSize.h
)

set( SOURCES
	sources/demos/objectDirections/objectDirectionData.cpp
	sources/demos/sounds/soundsStackData.cpp
	sources/demos/inputs/actionData.cpp
	sources/demos/positions/taggedPositionStackData.cpp
	sources/demos/positions/positionStackData.cpp
	sources/demos/objectsDestruction/matrixDemoData.cpp
	sources/demos/loading/loadDemosVectorsDataSize.cpp

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
	PRIVATE ../consts/sources
	PRIVATE ../commonFiles/sources
)

target_link_libraries(	
	${PROJECT_NAME}
	PRIVATE genericLib
	PRIVATE sdl2_wrapper
	PRIVATE commonFiles
)

set_target_properties( 	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS NO 
	LINKER_LANGUAGE CXX
)
