#ifndef GUI_LANGUAGE_TEXTS_BLOCKS_COMPONENTS_H
#define GUI_LANGUAGE_TEXTS_BLOCKS_COMPONENTS_H

#include "texts/textLoader.h"

struct AppLogFiles;

//Interface generator language
namespace igl{

struct TextsConfigElements
{
	std::string filePath;
	std::string fileLine;
	std::string identifier;
	std::string path;
	std::size_t fileLineNumber;
	unsigned expectedLines;
	
	explicit TextsConfigElements(const std::string& configFilePath);
	~TextsConfigElements() = default;
	TextsConfigElements( const TextsConfigElements& ) = delete;
	TextsConfigElements& operator= ( const TextsConfigElements& ) = delete;
	TextsConfigElements( TextsConfigElements&& ) = default;
	TextsConfigElements& operator= ( TextsConfigElements&& ) = default;
};
	
class Texts
{
private:
	std::vector< TextsBlocks > texts;
	bool isLoadingPerfect;
	
public:
	explicit Texts(AppLogFiles& logs, const std::string& configFilePath);
	~Texts() = default;
	Texts( const Texts& ) = delete;
	Texts& operator= ( const Texts& ) = delete;
	Texts( Texts&& ) = default;
	Texts& operator= ( Texts&& ) = default;
	
	operator bool() const;
	const std::string& getText(std::size_t fileIndex, std::size_t lineIndex) const;
	std::size_t size() const;
	std::size_t lineNumber(std::size_t index) const;
	
private:
	void readData(AppLogFiles& logs, std::istringstream& lineStream, igl::TextsConfigElements& elements);
};

}

#endif //GUI_LANGUAGE_TEXTS_BLOCKS_COMPONENTS_H