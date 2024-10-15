cmake_minimum_required(VERSION 3.13)

project( genericLib LANGUAGES CXX )

if(UNIX)
	include(GNUInstallDirs)
endif(UNIX)

set( HEADERS
		sources/fileSystem/fileSystem.h
		sources/fileSystem/copyFilesAndDirectories.h
		sources/fileSystem/pathsConcatenate.h
		sources/fileSystem/createNewElementFs.h
		sources/matrices/matrixStructs.h
		sources/matrices/matrix3D.h
		sources/matrices/matrix2D.h
		sources/time/dateAndTime.h
		sources/time/accurateTime.h
		sources/customTypes/positionTypes.h
		sources/customTypes/caseAnim.h
		sources/logging/logsStruct.h
		sources/logging/logFile.h
		sources/random/randomGenerator.h
		sources/texts/textLoader.h
		sources/arithmetic/customArithmetic.h
)

set( SOURCES
		sources/fileSystem/pathsConcatenate.cpp
		sources/fileSystem/createNewElementFs.cpp
		sources/fileSystem/copyFilesAndDirectories.cpp
		sources/matrices/matrixStructs.cpp
		sources/time/accurateTime.cpp
		sources/time/dateAndTime.cpp
		sources/customTypes/positionTypes.cpp
		sources/customTypes/caseAnim.cpp
		sources/logging/logFile.cpp
		sources/logging/logsStruct.cpp
		sources/random/randomGenerator.cpp
		sources/texts/textLoader.cpp
		sources/arithmetic/customArithmetic.cpp
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
)

target_link_libraries( ${PROJECT_NAME} )

set_target_properties(
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20 
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS ON
	LINKER_LANGUAGE CXX
)
