#ifndef INTERFACE_GENERATOR_LANGUAGE_CONSTS_H
#define INTERFACE_GENERATOR_LANGUAGE_CONSTS_H

/*
	'something' : this is an identifier of the language
	"something" : this is a user string (not determined by advance)
	[something] : this is a number
 
	Language description:
		Font nomenclature:
		'Font' "Font Path" [font size]
		
		Texts blocks nomenclature
		'TextsBlocks' "file path" [expected string lines]
		
		Text Texture nomenclature:
		'Texture' 'Text' 'TextNum' [TextsBlocksIndex] 'Color' [red value] [green value] [blue value] [alpha value] 
			('ProportionalPosition' or 'StaticPosition') [x coord] [y coord] 'CenterOnX' [1 or 0] 'CenterOnY' [1 or 0]
		
		Image Texture
		'Texture' 'Image' "texture path" ('ProportionalPosition' or 'StaticPosition') [x coord] [y coord] 'CenterOnX' [1 or 0] 'CenterOnY' [1 or 0]
  
*/  

namespace igl{
	namespace objId{
		constexpr char FONT_ID[] = "Font";
		constexpr char TEXTS_BLOCKS_ID[] = "TextsBlocks";
	}
	namespace texture{
		enum{ 	TEXTURE_IS_IMAGE, 
				TEXTURE_IS_TEXT, 
				TEXTURE_IS_MAX 
		};
		constexpr char TEXTURE_ID[] = "Texture";
		constexpr char TEXT_ID[] = "Text";
		constexpr char TEXT_NUM[] = "TextNum";
		constexpr char COLOR_ID[] = "Color";
		constexpr char IMAGE_ID[] = "Image";
		constexpr char PROP_POSITION_ID[] = "ProportionalPosition";
		constexpr char STATIC_POSITION_ID[] = "StaticPosition";
		constexpr char X_CENTER_ID[] = "CenterOnX";
		constexpr char Y_CENTER_ID[] = "CenterOnY";
		
		enum{ 	AWAIT_TEXTURE_ID, 
				AWAIT_TEXTURE_TYPE, 
				AWAIT_IMAGE_PATH, 
				AWAIT_TXT_BLOCKS_INDEX,
				AWAIT_COLOR_COMPONENTS,
				AWAIT_POSITION_COORD,
				AWAIT_CENTERED_POS
		};
	}
	
	namespace font{
		constexpr char FONT_PATH[] = "fontPath";
		constexpr char ARIAL_STD_PATH[] = "ArialFont";
		constexpr char NEURO_FONT_STD_PATH[] = "NeuropoliticalFont";
		constexpr char PROPORTIONAL_SIZE[] = "proportionalSize";
		constexpr char STATIC_SIZE[] = "staticSize";
	}
}

#endif //INTERFACE_GENERATOR_LANGUAGE_CONSTS_H