cmake_minimum_required(VERSION 3.13)

project( sdl2_wrapper LANGUAGES CXX)

if(UNIX)
	include(GNUInstallDirs)
endif(UNIX)

set(HEADERS
	sources/widgets/buttons/3TexturesButtonWidget.h
	sources/widgets/buttons/buttonFlatWidget.h
	sources/widgets/buttons/textButtonWidget.h
	sources/widgets/buttons/highlightButtonWidget.h
	sources/widgets/editBoxes/sint_editBox.h
	sources/widgets/editBoxes/bool_editBox.h
	sources/widgets/editBoxes/stringEditBox.h
	sources/widgets/editBoxes/boxesIncludes.h
	sources/widgets/editBoxes/subObjects/boxEvents.h
	sources/widgets/editBoxes/subObjects/editBoxes_consts.h
	sources/widgets/editBoxes/subObjects/boxRectDisplay.h
	sources/widgets/editBoxes/subObjects/boolBoxContentDisplay.h
	sources/widgets/editBoxes/subObjects/cursorDrawing.h
	sources/widgets/editBoxes/subObjects/boxContentDisplay.h
	sources/widgets/editBoxes/uint_editBox.h
	sources/initialization/sdl2MixerInit.h
	sources/initialization/sdl2TTF_Init.h
	sources/initialization/sdl2ModuleInit.h
	sources/text/sdl2ttf_font.h
	sources/texturing/textureLoader.h
	sources/texturing/horizontalGradientTexture.h
	sources/texturing/verticalGradientTexture.h
	sources/texturing/sdl2_sprite.h
	sources/texturing/rendererWindow.h
	sources/texturing/texturePosition.h
	sources/texturing/loadSDL2.h
	sources/texturing/texturesCombo.h
	sources/joystick/joystickEntity.h
	sources/versioning/makeStringFromVersion.h
	sources/consts/fontsPaths.h
	sources/sounds/loadSound.h
	sources/prefPath/prefPathFinder.h
	sources/advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/fontsScriptLoader.h
	sources/advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h
	sources/advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/textsBlocksComponent.h
	sources/advancedDrawing/interfaceGeneratorLanguage/interfaceGeneratorConsts.h
	sources/advancedDrawing/interfaceGeneratorLanguage/optionsStructs/texturesOptions.h
	sources/advancedDrawing/interfaceGeneratorLanguage/optionsStructs/colorComponent.h
	sources/advancedDrawing/interfaceGeneratorLanguage/optionsStructs/fontsOptions.h
	sources/advancedDrawing/texturesLoading/3dimTexturesLoading.h
	sources/advancedDrawing/texturesLoading/2dimTexturesLoading.h
	sources/advancedDrawing/texturesLoading/animFileTextures.h
	sources/advancedDrawing/texturesLoading/fileTexturesList.h
	sources/advancedDrawing/texturesDrawing/animTexturesDrawing.h
	sources/advancedDrawing/texturesDrawing/3dimTexturesDrawing.h
	sources/advancedDrawing/texturesDrawing/2dimTexturesDrawing.h
	sources/advancedDrawing/texturesDrawing/constAnimationDrawing.h
	sources/keycodes/keycodesOverload.h
	sources/wrappers/ttfPtrWrapper.h
	sources/wrappers/hapticPtrWrapper.h
	sources/wrappers/mixerPtrWrapper.h
	sources/wrappers/rectStream.h
	sources/wrappers/joystickPtrWrapper.h
	sources/wrappers/sdl2_ptr.h
)

set(SOURCES
	sources/widgets/buttons/textButtonWidget.cpp
	sources/widgets/buttons/3TexturesButtonWidget.cpp
	sources/widgets/buttons/buttonFlatWidget.cpp
	sources/widgets/buttons/highlightButtonWidget.cpp
	sources/widgets/editBoxes/stringEditBox.cpp
	sources/widgets/editBoxes/bool_editBox.cpp
	sources/widgets/editBoxes/subObjects/boxRectDisplay.cpp
	sources/widgets/editBoxes/subObjects/boxContentDisplay.cpp
	sources/widgets/editBoxes/subObjects/cursorDrawing.cpp
	sources/widgets/editBoxes/subObjects/boxEvents.cpp
	sources/widgets/editBoxes/subObjects/boolBoxContentDisplay.cpp
	sources/widgets/editBoxes/sint_editBox.cpp
	sources/widgets/editBoxes/uint_editBox.cpp
	sources/initialization/sdl2ModuleInit.cpp
	sources/initialization/sdl2MixerInit.cpp
	sources/initialization/sdl2TTF_Init.cpp
	sources/text/sdl2ttf_font.cpp
	sources/texturing/sdl2_sprite.cpp
	sources/texturing/texturesCombo.cpp
	sources/texturing/horizontalGradientTexture.cpp
	sources/texturing/loadSDL2.cpp
	sources/texturing/textureLoader.cpp
	sources/texturing/texturePosition.cpp
	sources/texturing/verticalGradientTexture.cpp
	sources/texturing/rendererWindow.cpp
	sources/joystick/joystickEntity.cpp
	sources/versioning/makeStringFromVersion.cpp
	sources/sounds/loadSound.cpp
	sources/prefPath/prefPathFinder.cpp
	sources/advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.cpp
	sources/advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/textsBlocksComponent.cpp
	sources/advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/fontsScriptLoader.cpp
	sources/advancedDrawing/interfaceGeneratorLanguage/optionsStructs/fontsOptions.cpp
	sources/advancedDrawing/interfaceGeneratorLanguage/optionsStructs/texturesOptions.cpp
	sources/advancedDrawing/interfaceGeneratorLanguage/optionsStructs/colorComponent.cpp
	sources/advancedDrawing/texturesLoading/animFileTextures.cpp
	sources/advancedDrawing/texturesLoading/fileTexturesList.cpp
	sources/advancedDrawing/texturesLoading/2dimTexturesLoading.cpp
	sources/advancedDrawing/texturesLoading/3dimTexturesLoading.cpp
	sources/advancedDrawing/texturesDrawing/animTexturesDrawing.cpp
	sources/advancedDrawing/texturesDrawing/2dimTexturesDrawing.cpp
	sources/advancedDrawing/texturesDrawing/constAnimationDrawing.cpp
	sources/advancedDrawing/texturesDrawing/3dimTexturesDrawing.cpp
	sources/keycodes/keycodesOverload.cpp
	sources/wrappers/rectStream.cpp
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
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
	PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
	PRIVATE ${SDL2_MIXER_INCLUDE_DIRS}
	PRIVATE sources
	PRIVATE ../genericLib/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PUBLIC ${SDL2_LIBRARIES} 
	PUBLIC ${SDL2_IMAGE_LIBRARIES} 
	PUBLIC ${SDL2_TTF_LIBRARIES} 
	PUBLIC ${SDL2_MIXER_LIBRARIES}
	PRIVATE genericLib
)

set_target_properties(	
	${PROJECT_NAME} 
	PROPERTIES 
	CXX_STANDARD 20 
	CXX_STANDARD_REQUIRED YES 
	CXX_EXTENSIONS ON
	LINKER_LANGUAGE CXX
)
