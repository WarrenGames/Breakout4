cmake_minimum_required(VERSION 3.13)

project( gameSaveAndLoad LANGUAGES CXX )

set( HEADERS
		sources/gameSlots/slotConsts.h
		sources/gameSlots/gameSlotData.h
		sources/exceptions/writeErrorExcept.h
		sources/exceptions/readErrorExcept.h
		sources/saving/saveData.h
		sources/crossLevel/playerData.h
		sources/crossLevel/levelsInfos.h
		sources/loading/loadData.h
)

set( SOURCES
		sources/gameSlots/gameSlotData.cpp
		sources/exceptions/readErrorExcept.cpp
		sources/exceptions/writeErrorExcept.cpp
		sources/saving/saveData.cpp
		sources/crossLevel/levelsInfos.cpp
		sources/crossLevel/playerData.cpp
		sources/loading/loadData.cpp
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

target_include_directories(
	${PROJECT_NAME}
	PRIVATE sources
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/genericLib
	PRIVATE ../consts/sources
	PRIVATE ../commonFiles/sources
	PRIVATE ../demosLibrary/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE genericLib
	PRIVATE commonFiles
	PRIVATE demosLibrary
)
						
set_target_properties( 	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS NO 
	LINKER_LANGUAGE CXX
)
