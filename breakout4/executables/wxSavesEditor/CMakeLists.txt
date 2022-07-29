cmake_minimum_required( VERSION 3.0 )

project( wxSavesEditor LANGUAGES CXX )

include( ${wxWidgets_USE_FILE} )

set( HEADERS
		sources/appStart/main.h
		sources/appStart/appStartData.h
		sources/consts/consts.h
		sources/data/fileSaving.h
		sources/data/fileLoading.h
		sources/data/gameSlots.h
		sources/data/gameSavePath.h
		sources/interface/headersInterface.h
		sources/interface/bagBonusesInterface.h
		sources/interface/myFrame.h
		sources/interface/menuBar.h
		sources/interface/gameObjectsInterface.h
		sources/interface/menuItemsID.h
)

set( SOURCES
		sources/appStart/main.cpp
		sources/appStart/appStartData.cpp
		sources/data/fileLoading.cpp
		sources/data/gameSavePath.cpp
		sources/data/fileSaving.cpp
		sources/data/gameSlots.cpp
		sources/interface/bagBonusesInterface.cpp
		sources/interface/menuBar.cpp
		sources/interface/gameObjectsInterface.cpp
		sources/interface/headersInterface.cpp
		sources/interface/myFrame.cpp
)

add_executable(	${PROJECT_NAME} 
				WIN32
				${SOURCES} 
				${HEADERS} 
				${INC_DIRS}
)

target_include_directories(	${PROJECT_NAME}
							PRIVATE ${SDL2_INCLUDE_DIRS}
							PRIVATE sources
							PRIVATE ../../libs/genericLib/sources
							PRIVATE ../../libs/gameSaveAndLoad/sources
							PRIVATE ../../libs/consts/sources
							PRIVATE ../../libs/commonFiles/sources
							PRIVATE ../../libs/wxPrefPath/sources
)

target_link_libraries(	${PROJECT_NAME} 
						${wxWidgets_LIBRARIES}
						${SDL2_LIBRARIES} 
						genericLib
						wxPrefPath
						gameSaveAndLoad
)

set_target_properties(	${PROJECT_NAME} 
						PROPERTIES 
						CXX_STANDARD 20
						CXX_STANDARD_REQUIRED YES 
						CXX_EXTENSIONS NO 
						LINKER_LANGUAGE CXX
)
