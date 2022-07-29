#ifndef INTERFACE_GENERATOR_LANGUAGE_FONTS_OPTIONS_H
#define INTERFACE_GENERATOR_LANGUAGE_FONTS_OPTIONS_H

#include <string>

namespace igl{

namespace font{
	
	struct Description
	{
		std::string scriptFilePath;
		std::string fileLine;
		std::string identifier;
		std::string fontPath;
		unsigned fontSize;
		unsigned fileLineNumber;
		unsigned squareSize;
		bool isLoadingPerfect;
		
		explicit Description(const std::string& toOpenFile, unsigned squareSize_);
	};

}

}

#endif //INTERFACE_GENERATOR_LANGUAGE_FONTS_OPTIONS_H