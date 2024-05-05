#ifndef LOAD_TEXT_FILE_LINE_H
#define LOAD_TEXT_FILE_LINE_H

#include "fileSystem/fileSystem.h"
#include <vector>
#include <string>
#include <iosfwd>

class LogFile;

class TextsBlocks
{
private:
	std::string errorString;
	std::vector<std::string> texts;
	bool isLoadingPerfect;
	
public:
	explicit TextsBlocks();
	explicit TextsBlocks(LogFile& log, const fs::path& filePath);
	explicit TextsBlocks(LogFile& log, const fs::path& filePath, std::size_t expectedStringsNumber);
	explicit TextsBlocks(std::string& logString, const std::string& filePath, std::size_t expectedStringsNumber);
	explicit TextsBlocks(std::string& logString, const std::string& filePath);
	~TextsBlocks() = default;
	TextsBlocks( const TextsBlocks& ) = default;
	TextsBlocks& operator= ( const TextsBlocks& ) = default;
	TextsBlocks( TextsBlocks&& ) = default;
	TextsBlocks& operator= ( TextsBlocks&& ) = default;
	
	void initializeTexts(LogFile& log, const fs::path& filePath, std::size_t expectedStringsNumber);
	operator bool () const;
	bool wasReadingPerfect() const;
	const std::vector<std::string>& getTexts() const;
	const std::string& operator[](std::size_t lineNumber) const;
	std::size_t size() const;
	
	const std::vector<std::string>::const_iterator begin() const;
	const std::vector<std::string>::const_iterator end() const;
	std::vector<std::string>::iterator begin();
	std::vector<std::string>::iterator end();
	
private:
	void loadTextLines(std::ifstream& textFile);
	void checkExpectedLoadedTexts(LogFile& log, const fs::path& filePath, std::size_t expectedStringsNumber);
	void checkExpectedLoadedTexts(std::string& logString, const fs::path& filePath, std::size_t expectedStringsNumber);
	void loadWithExpectedLines(LogFile& log, const fs::path& filePath, std::size_t expectedLinesNumber);
};

#endif //LOAD_TEXT_FILE_LINE_H