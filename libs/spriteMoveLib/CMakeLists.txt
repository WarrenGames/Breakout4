cmake_minimum_required( VERSION 3.0 )

project( spriteMoveLib LANGUAGES CXX )

if(UNIX)
	include(GNUInstallDirs)
endif(UNIX)

set(HEADERS
		sources/spriteMove/moveVectorSeriesHandle.h
		sources/spriteMove/pathVector.h
		sources/spriteMove/starType.h
		sources/spriteMove/orientation.h
		sources/spriteMove/moveInfos.h
		sources/spriteMove/movements.h
		sources/spriteMove/moveConsts.h
		sources/spriteMove/createPathData.h
		sources/spriteMove/spriteMoveData.h
		sources/spriteMove/pi.h
		sources/spriteMove/objectMove.h
)

set(SOURCES
		sources/spriteMove/starType.cpp
		sources/spriteMove/orientation.cpp
		sources/spriteMove/movements.cpp
		sources/spriteMove/objectMove.cpp
		sources/spriteMove/createPathData.cpp
		sources/spriteMove/spriteMoveData.cpp
		sources/spriteMove/pathVector.cpp
		sources/spriteMove/moveVectorSeriesHandle.cpp
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
	PRIVATE sources
	PRIVATE ../genericLib/sources
)

target_link_libraries(${PROJECT_NAME} 
	genericLib
)

set_target_properties(	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20 
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS ON
	LINKER_LANGUAGE CXX
)

if( UNIX )
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
endif( UNIX )