#include "texts/textLoader.h"
#include "logging/logFile.h"
#include <cassert>

constexpr char ErrorString[] = "error";

TextsBlocks::TextsBlocks():
	errorString{ErrorString},
	isLoadingPerfect{true}
{
	
}

TextsBlocks::TextsBlocks(LogFile& log, const fs::path& filePath):
	errorString{ErrorString},
	isLoadingPerfect{true}
{
	if( std::ifstream languageFile{filePath} )
	{
		loadTextLines(languageFile);
	}
	else{
		isLoadingPerfect = false;
		log.wrFileOpeningError(filePath.string(), "language text file");
	}
}

TextsBlocks::TextsBlocks(LogFile& log, const fs::path& filePath, std::size_t expectedStringsNumber):
	errorString{ErrorString},
	isLoadingPerfect{true}
{
	if( std::ifstream languageFile{filePath} )
	{
		loadTextLines(languageFile);
		checkExpectedLoadedTexts(log, filePath, expectedStringsNumber);
	}
	else{
		log.wrFileOpeningError(filePath.string(), "load language text file");
		isLoadingPerfect = false;
	}
}

TextsBlocks::TextsBlocks(std::string& logString, const std::string& filePath, std::size_t expectedStringsNumber):
	errorString{ErrorString},
	isLoadingPerfect{true}
{
	if( std::ifstream languageFile{filePath} )
	{
		loadTextLines(languageFile);
		checkExpectedLoadedTexts(logString, filePath, expectedStringsNumber);
	}
	else{
		logString = "Error: couldn't open '" + filePath + "' file in order to load language text file.";
		isLoadingPerfect = false;
	}
}

TextsBlocks::TextsBlocks(std::string& logString, const std::string& filePath):
	errorString{ErrorString},
	isLoadingPerfect{true}
{
	if( std::ifstream languageFile{filePath} )
	{
		loadTextLines(languageFile);
	}
	else{
		logString = "Error: couldn't open '" + filePath + "' file in order to load language text file.";
		isLoadingPerfect = false;
	}
}

void TextsBlocks::initializeTexts(LogFile& log, const fs::path& filePath, std::size_t expectedStringsNumber)
{
	errorString = ErrorString;
	isLoadingPerfect = true;
	if( std::ifstream languageFile{ filePath } )
	{
		loadTextLines(languageFile);
		checkExpectedLoadedTexts(log, filePath, expectedStringsNumber);
	}
	else{
		log.wrFileOpeningError(filePath, "load language text file");
		isLoadingPerfect = false;
	}
}

TextsBlocks::operator bool() const
{
	return isLoadingPerfect;
}

bool TextsBlocks::wasReadingPerfect() const
{
	return isLoadingPerfect;
}

const std::vector<std::string>& TextsBlocks::getTexts() const
{
	return texts;
}

const std::string& TextsBlocks::operator[](std::size_t lineNumber) const
{
	if( lineNumber < texts.size() )
	{
		return texts[lineNumber];
	}
	else{
		return errorString;
	}
}

std::size_t TextsBlocks::size() const
{
	return texts.size();
}

const std::vector<std::string>::const_iterator TextsBlocks::begin() const
{
	return texts.cbegin();
}

const std::vector<std::string>::const_iterator TextsBlocks::end() const
{
	return texts.cend();
}

std::vector<std::string>::iterator TextsBlocks::begin()
{
	return texts.begin();
}

std::vector<std::string>::iterator TextsBlocks::end()
{
	return texts.end();
}

void TextsBlocks::loadTextLines(std::ifstream& textFile)
{
	std::string fileLine;
	while(std::getline(textFile, fileLine) )
	{
		if( fileLine[0] != '#' )
		{
			texts.emplace_back(fileLine);
		}
	}
}

void TextsBlocks::checkExpectedLoadedTexts(LogFile& log, const fs::path& filePath, std::size_t expectedStringsNumber)
{
	if( texts.size() != expectedStringsNumber )
	{
		log << std::string{"Error: loading lang file '" + filePath.string() + "' failed because size: " + std::to_string(texts.size() )
										+ " is different from expected " + std::to_string(expectedStringsNumber) + " texts"};
		isLoadingPerfect = false;
	}
}

void TextsBlocks::checkExpectedLoadedTexts(std::string& logString, const fs::path& filePath, std::size_t expectedStringsNumber)
{
	if( texts.size() != expectedStringsNumber )
	{
		logString = std::string{"Error: loading lang file '" + filePath.string() + "' failed because size: " + std::to_string(texts.size() )
										+ " is different from expected " + std::to_string(expectedStringsNumber) + " texts"};
		isLoadingPerfect = false;
	}
}