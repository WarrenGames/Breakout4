cmake_minimum_required(VERSION 3.0)

project( gameSaveAndLoad LANGUAGES CXX )

set( HEADERS
		sources/gameSlots/slotConsts.h
		sources/gameSlots/gameSlotData.h
		sources/exceptions/writeErrorExcept.h
		sources/exceptions/readErrorExcept.h
		sources/saving/saveData.h
		sources/crossLevel/playerData.h
		sources/loading/loadData.h
)

set( SOURCES
		sources/gameSlots/gameSlotData.cpp
		sources/exceptions/readErrorExcept.cpp
		sources/exceptions/writeErrorExcept.cpp
		sources/saving/saveData.cpp
		sources/crossLevel/playerData.cpp
		sources/loading/loadData.cpp
)

add_library(	${PROJECT_NAME} 
				STATIC
				${SOURCES} 
				${HEADERS} 
				${INC_DIRS}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE sources
	PRIVATE ../../libs/genericLib/sources
	PRIVATE ../../libs/consts/sources
	PRIVATE ../../libs/commonFiles/sources
)

target_link_libraries(	${PROJECT_NAME} 
						genericLib
						commonFiles
)
						
set_target_properties( 	${PROJECT_NAME} 
						PROPERTIES 
						PUBLIC_HEADER "${HEADERS}" 
						CXX_STANDARD 20
						CXX_STANDARD_REQUIRED YES 
						CXX_EXTENSIONS NO 
						LINKER_LANGUAGE CXX
)
