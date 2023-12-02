#ifndef ONE_PLAYER_GRID_PANEL_H
#define ONE_PLAYER_GRID_PANEL_H

#include "interface/mainLayout/event.h"
#include "interface/currentGrid/onePlayerGrid/data.h"
#include "wx/panel.h"
#include <string>

class wxTextCtrl;
class wxNotebook;
class wxPaintEvent;
class OnePBricksTextures;
struct Offset;

class OnePlayerGridPanel : public wxPanel
{
private:
	const wxColour darkGray;
	GridData data;
	const OnePBricksTextures& tex;
	const BrickData& selectedBrick;
	InterfaceEvents events;
	std::string filePath;

public:
	explicit OnePlayerGridPanel(wxNotebook *notebook, std::size_t width, std::size_t height, const OnePBricksTextures& textures, const BrickData& brickData);
	~OnePlayerGridPanel() = default;
	OnePlayerGridPanel(const OnePlayerGridPanel&) = delete;
	OnePlayerGridPanel& operator= (const OnePlayerGridPanel&) = delete;
	
	void loadGridFromFile(const std::string& gridFilePath);
	void saveGridToFile(wxTextCtrl& logWindow, const std::string& gridFilePath);
	void saveGridToSameFile(wxTextCtrl& logWindow);
	void resetGrid();
	void drawGrid(wxPaintEvent& paintEvent);
	void changeSquare(std::size_t width, std::size_t height, const BrickData& brickData);
	
	int getPanelXPosition() const;
	int getPanelYPosition() const;
	
	void changeGridData(wxMouseEvent& event);
	void deleteGridData(wxMouseEvent& event);
	
	void appendAccordingToSelected(const Offset& squareCoords);
	
	void shiftDownData();
	void shiftUpData();
};

#endif //ONE_PLAYER_GRID_PANEL_H