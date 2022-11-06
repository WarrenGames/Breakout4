cmake_minimum_required(VERSION 3.0)

project( breakout4_consts LANGUAGES CXX )

set( HEADERS
		sources/consts/duelsGridConsts.h
		sources/consts/rimsConsts.h
		sources/consts/onePlayerGridConsts.h
		sources/consts/onePlayerLevelConsts.h
		sources/consts/onePlayerBonusesConsts.h
		sources/consts/hellConsts.h
)

add_library(
	${PROJECT_NAME} 
	STATIC
	${HEADERS} 
)

target_link_libraries(	${PROJECT_NAME} )
						
set_target_properties( 	${PROJECT_NAME} 
						PROPERTIES 
						PUBLIC_HEADER "${HEADERS}" 
						CXX_STANDARD 20
						CXX_STANDARD_REQUIRED YES 
						CXX_EXTENSIONS NO 
						LINKER_LANGUAGE CXX
)
