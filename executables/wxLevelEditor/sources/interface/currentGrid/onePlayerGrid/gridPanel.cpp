#include "interface/currentGrid/onePlayerGrid/gridPanel.h"
#include "interface/currentGrid/onePlayerGrid/bricksTextures.h"
#include "customTypes/positionTypes.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerGridConsts.h"
#include "wx/notebook.h"
#include "wx/dcclient.h"
#include "wx/textctrl.h"

OnePlayerGridPanel::OnePlayerGridPanel(wxNotebook *notebook, std::size_t width, std::size_t height, const OnePBricksTextures& textures, const BrickData& brickData):
	wxPanel{ notebook, wxID_ANY, wxPoint{-1, -1}, wxSize{EditorGridWidth, EditorGridHeight} }, 
	darkGray{ wxT("#4f5049") },
	data{width, height},
	tex{textures},
	selectedBrick{ brickData }
{
	SetBackgroundColour(darkGray);
	
	Bind(wxEVT_PAINT, &OnePlayerGridPanel::drawGrid, this );
	Bind(wxEVT_LEFT_DOWN, &OnePlayerGridPanel::changeGridData, this);
	Bind(wxEVT_MIDDLE_DOWN, &OnePlayerGridPanel::deleteGridData, this);
}

void OnePlayerGridPanel::loadGridFromFile(const std::string& gridFilePath)
{
	data.readFile(gridFilePath);
	filePath = gridFilePath;
}

void OnePlayerGridPanel::saveGridToFile(wxTextCtrl& logWindow, const std::string& gridFilePath)
{
	data.saveToFile(logWindow, gridFilePath);
}

void OnePlayerGridPanel::saveGridToSameFile(wxTextCtrl& logWindow)
{
	data.saveToFile(logWindow, filePath);
}

void OnePlayerGridPanel::resetGrid()
{
	data.resetMatrix();
}

void OnePlayerGridPanel::drawGrid(wxPaintEvent& paintEvent)
{
	wxPaintDC drawingContext{this};
	Offset position;
	for( std::size_t height{ 0 }; height < data.height(); ++height)
	{
		position.y = static_cast<int>(height) * SQR_SIZE;
		for( std::size_t width{ 0 }; width < data.width(); ++width)
		{
			position.x = static_cast<int>(width) * SQR_SIZE;
			tex.drawSingleBrick(drawingContext, data.getData(width, height), position);
		}
	}
}

void OnePlayerGridPanel::changeSquare(std::size_t width, std::size_t height, const BrickData& brickData)
{
	data.changeSquare(width, height, brickData);
}

int OnePlayerGridPanel::getPanelXPosition() const
{
	return this->GetScreenPosition().x;
}

int OnePlayerGridPanel::getPanelYPosition() const
{
	return this->GetScreenPosition().y;
}

void OnePlayerGridPanel::changeGridData(wxMouseEvent& event)
{
	events.updateMouseEvents();
	Offset square{ 	( events.mouseState.GetX() - getPanelXPosition() ) / SQR_SIZE, 
					( events.mouseState.GetY() - getPanelYPosition() ) / SQR_SIZE };
	
	if( events.mouseState.LeftIsDown() && square.x < EditorGridSquaresWidth && square.y < EditorGridSquaresHeight )
	{
		//changeSquare(square.x, square.y, selectedBrick );
		appendAccordingToSelected(square);
		Refresh();
	}
}

void OnePlayerGridPanel::deleteGridData(wxMouseEvent& event)
{
	events.updateMouseEvents();
	Offset square{  ( events.mouseState.GetX() - getPanelXPosition() ) / SQR_SIZE, 
					( events.mouseState.GetY() - getPanelYPosition() ) / SQR_SIZE };
					
	if( events.mouseState.MiddleIsDown() && square.x < EditorGridSquaresWidth && square.y < EditorGridSquaresHeight )
	{
		changeSquare(square.x, square.y, BrickData{0, 0} );
		Refresh();
	}
}

void OnePlayerGridPanel::appendAccordingToSelected(const Offset& squareCoords)
{
	if( bricks::index::RichBrick == selectedBrick.index && squareCoords.x + 1 < EditorGridSquaresWidth )
	{
		changeSquare(squareCoords.x, squareCoords.y, selectedBrick);
		changeSquare(squareCoords.x + 1, squareCoords.y, BrickData{ selectedBrick.index, selectedBrick.property + 1 } );
	}
	else{
		changeSquare(squareCoords.x, squareCoords.y, selectedBrick);
	}
}

void OnePlayerGridPanel::shiftDownData()
{
	data.shiftDownData();
}

void OnePlayerGridPanel::shiftUpData()
{
	data.shiftUpData();
}