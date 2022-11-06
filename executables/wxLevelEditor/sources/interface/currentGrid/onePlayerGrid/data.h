#ifndef GUI_CURRENT_GRID_DATA_H
#define GUI_CURRENT_GRID_DATA_H

#include "matrices/matrix2D.h"
#include "interface/currentGrid/onePlayerGrid/brickData.h"
#include <string>

class wxTextCtrl;

class GridData
{
private:
	const std::string filePath;
	MatrixTemp2D<BrickData> matrix;
	
public:
	explicit GridData(std::size_t width, std::size_t height);
	explicit GridData(std::size_t width, std::size_t height, const std::string& gridFilePath);
	~GridData() = default;
	
	std::size_t width() const;
	std::size_t height() const;
	const std::string& getPath() const;
	
	void changeSquare(std::size_t width, std::size_t height, const BrickData& brickData);
	const BrickData& getData(std::size_t width, std::size_t height) const;
	
	void resetMatrix();
	void readFile(const std::string& gridFilePath);
	void saveToFile(wxTextCtrl& logWindow, const std::string& gridFilePath) const;
	
	void shiftDownData();
	void shiftUpData();
	void clearLine(std::size_t height);
};

#endif //GUI_CURRENT_GRID_DATA_H