cmake_minimum_required(VERSION 3.13)

project( wxPrefPath LANGUAGES CXX )

include( ${wxWidgets_USE_FILE} )

set( HEADERS
	sources/prefPath/wxPrefPath.h
)

set( SOURCES
	sources/prefPath/wxPrefPath.cpp
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
	PRIVATE ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE ${wxWidgets_LIBRARIES}
	PRIVATE ${SDL2_LIBRARIES} 
)

set_target_properties(	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS NO 
	LINKER_LANGUAGE CXX
)

