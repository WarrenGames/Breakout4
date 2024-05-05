#include "interface/currentGrid/onePlayerGrid/data.h"
#include "consts/onePlayerGridConsts.h"
#include "wx/textctrl.h"
#include <sstream>
#include <fstream>

GridData::GridData(std::size_t width, std::size_t height):
	matrix{width, height}
{
	
}

GridData::GridData(std::size_t width, std::size_t height, const std::string& gridFilePath):
	filePath{gridFilePath},
	matrix{width, height}
{
	readFile(gridFilePath);
}

std::size_t GridData::width() const
{
	return matrix.width();
}

std::size_t GridData::height() const
{
	return matrix.height();
}

const std::string& GridData::getPath() const
{
	return filePath;
}

void GridData::changeSquare(std::size_t width, std::size_t height, const BrickData& brickData)
{
	matrix(width, height) = brickData;
}

const BrickData& GridData::getData(std::size_t width, std::size_t height) const
{
	return matrix(width, height);
}

void GridData::resetMatrix()
{
	matrix.fillMatrix(BrickData{});
}

void GridData::readFile(const std::string& gridFilePath)
{
	if( std::ifstream gridFile{gridFilePath} )
	{
		std::string fileLine;
		BrickData data;
		std::size_t width{0};
		std::size_t height{0};
		
		while( std::getline(gridFile, fileLine) )
		{
			std::istringstream lineStream{fileLine};
			if( lineStream >> height >> width >> data.index >> data.property )
			{
				matrix(width, height) = data;
			}
		}
	}
}

void GridData::saveToFile(wxTextCtrl& logWindow, const std::string& gridFilePath) const
{
	if( std::ofstream gridFile{gridFilePath} )
	{
		for( std::size_t height{0} ; height < matrix.height() ; ++height )
		{
			for( std::size_t width{0} ; width < matrix.width() ; ++width )
			{
				if( matrix(width, height).index != bricks::index::NoBrick )
				{
					gridFile << height << " " << width << " " << matrix(width, height).index << " " << matrix(width, height).property << "\n";
				}
			}
		}
	}
	else{
		logWindow << "Error: couldn't open '" << gridFilePath << "' file in order to save a grid of breakout4.\n";
	}
}

void GridData::shiftDownData()
{
	for( int height{ static_cast<int>( matrix.height() ) - 1 } ; height > 0 ; --height )
	{
		for( std::size_t width{0} ; width < matrix.width() ; ++width )
		{
			matrix(width, height) = matrix(width, height - 1); 
		}
	}
	clearLine( 0 );
}

void GridData::shiftUpData()
{
	for( std::size_t height{ 0 } ; height < matrix.height() - 1 ; ++height )
	{
		for( std::size_t width{0} ; width < matrix.width() ; ++width )
		{
			matrix(width, height) = matrix(width, height + 1 );
		}
	}
	clearLine(matrix.height() - 1);
}

void GridData::clearLine(std::size_t height)
{
	for( std::size_t width{0} ; width < matrix.width() ; ++width )
	{
		matrix(width, height ).index = 0;
		matrix(width, height ).property = 0;
	}
}