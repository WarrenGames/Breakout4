cmake_minimum_required(VERSION 3.13)

project( breakout4_consts LANGUAGES CXX )

set( HEADERS
	sources/consts/duelsGridConsts.h
	sources/consts/duelsSounds.h
	sources/consts/rimsConsts.h
	sources/consts/duelsConstexpr.h
	sources/consts/onePlayerGridConsts.h
	sources/consts/onePlayerMenuItems.h
	sources/consts/onePlayerLevelConsts.h
	sources/consts/optionsLanguageConsts.h
	sources/consts/onePlayerBonusesConsts.h
	sources/consts/hellConsts.h
	sources/consts/singlePlayerDemoConsts.h
)

add_library(
	${PROJECT_NAME} 
	STATIC
	${HEADERS} 
)

target_link_libraries(	
	${PROJECT_NAME} 
)
						
set_target_properties( 	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS NO 
	LINKER_LANGUAGE CXX
)
