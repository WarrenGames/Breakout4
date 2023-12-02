cmake_minimum_required( VERSION 3.13 )

project( wxLevelEditor LANGUAGES CXX )

include( ${wxWidgets_USE_FILE} )

set( HEADERS
		sources/appStart/main.h
		sources/pathsStrings/pathsFunctions.h
		sources/consts/constexprScreen.h
		sources/consts/pathsConsts.h
		sources/consts/buttonEventsID.h
		sources/interface/toolBar/brickChoiceMenusBar.h
		sources/interface/toolBar/toolsMenusBar.h
		sources/interface/toolBar/menusBar.h
		sources/interface/toolBar/fileMenuComponents.h
		sources/interface/toolBar/toolbarIcons.h
		sources/interface/selectedBrick/selectedBrickPanel.h
		sources/interface/currentGrid/duelsGrid/bricksTextures.h
		sources/interface/currentGrid/onePlayerGrid/brickData.h
		sources/interface/currentGrid/onePlayerGrid/data.h
		sources/interface/currentGrid/onePlayerGrid/bricksTextures.h
		sources/interface/currentGrid/onePlayerGrid/gridPanel.h
		sources/interface/mainLayout/event.h
		sources/interface/mainLayout/mainFrame.h
)

set( SOURCES
		sources/appStart/main.cpp
		sources/pathsStrings/pathsFunctions.cpp
		sources/interface/toolBar/menusBar.cpp
		sources/interface/toolBar/fileMenuComponents.cpp
		sources/interface/toolBar/brickChoiceMenusBar.cpp
		sources/interface/toolBar/toolbarIcons.cpp
		sources/interface/toolBar/toolsMenusBar.cpp
		sources/interface/selectedBrick/selectedBrickPanel.cpp
		sources/interface/currentGrid/duelsGrid/bricksTextures.cpp
		sources/interface/currentGrid/onePlayerGrid/bricksTextures.cpp
		sources/interface/currentGrid/onePlayerGrid/data.cpp
		sources/interface/currentGrid/onePlayerGrid/gridPanel.cpp
		sources/interface/currentGrid/onePlayerGrid/brickData.cpp
		sources/interface/mainLayout/mainFrame.cpp
		sources/interface/mainLayout/event.cpp
)

add_executable(	
	${PROJECT_NAME} 
	WIN32
	${SOURCES} 
	${HEADERS} 
	${INC_DIRS}
)

target_include_directories(	
	${PROJECT_NAME}
	PRIVATE sources
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/genericLib
	PRIVATE ${WARREN_LIBS_INCLUDES_PATH}/wxPrefPath
	PRIVATE ../../libraries/commonFiles/sources
	PRIVATE ../../libraries/consts/sources
)

target_link_libraries(
	${PROJECT_NAME} 
	PRIVATE wxPrefPath
	PUBLIC ${SDL2_LIBRARIES}
	PRIVATE ${wxWidgets_LIBRARIES}
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
