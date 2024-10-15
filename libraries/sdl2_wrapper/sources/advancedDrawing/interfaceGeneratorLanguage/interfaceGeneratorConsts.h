#ifndef INTERFACE_GENERATOR_LANGUAGE_CONSTS_H
#define INTERFACE_GENERATOR_LANGUAGE_CONSTS_H

/*
	'something' : this is an identifier or a key word of the language
	"something" : this is a user string (not determined by advance)
	[something] : this is a number
 
	Language description:
		Font nomenclature:
		'Font' "Font Path" [font size]
		
		Texts blocks nomenclature:
		'TextsBlocks' "file path" [expected string lines]
		
		Text Texture nomenclature:
		'Texture' 'Text' 'TextNum' [TextsBlocksIndex] 'Color' [red value] [green value] [blue value] [alpha value] 
			('ProportionalPosition' or 'StaticPosition') [x coord] [y coord] 'CenterOnX' [1 or 0] 'CenterOnY' [1 or 0]
		
		Image Texture nomenclature:
		'Texture' 'Image' "texture path" ('ProportionalPosition' or 'StaticPosition') [x coord] [y coord] 'CenterOnX' [1 or 0] 'CenterOnY' [1 or 0]
  
*/  

namespace igl{
	namespace objId{
		constexpr char FontId[] = "Font";
		constexpr char TextsBlocksId[] = "TextsBlocks";
	}
	namespace texture{
		enum{ 	TextureIsImage, 
				TextureIsText, 
				TextureIsMax 
		};
		constexpr char TextureId[] = "Texture";
		constexpr char TextId[] = "Text";
		constexpr char TextNum[] = "TextNum";
		constexpr char ColorId[] = "Color";
		constexpr char ImageId[] = "Image";
		constexpr char ProportionalPositionId[] = "ProportionalPosition";
		constexpr char StaticPositionId[] = "StaticPosition";
		constexpr char X_CenterId[] = "CenterOnX";
		constexpr char Y_CenterId[] = "CenterOnY";
		
		enum{ 	AwaitTextureId, 
				AwaitTextureType, 
				AwaitImagePath, 
				AwaitTextsBlocksIndex,
				AwaitColorComponents,
				AwaitPositionCoordinates,
				AwaitCenteredPosition
		};
	}
	
	namespace font{
		constexpr char FontPath[] = "fontPath";
		constexpr char ArialStandardPath[] = "ArialFont";
		constexpr char NeuroFontStandardPath[] = "NeuropoliticalFont";
		constexpr char ProportionalSize[] = "proportionalSize";
		constexpr char StaticSize[] = "staticSize";
	}
}

#endif //INTERFACE_GENERATOR_LANGUAGE_CONSTS_H