#include "interface/selectedBrick/selectedBrickPanel.h"
#include "interface/mainLayout/mainFrame.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/constexprScreen.h"
#include "wx/dcclient.h"
#include <cassert>

SelectedBrickPanel::SelectedBrickPanel(MainFrame *mainFrame, OnePBricksTextures& bricksTextures):
	wxPanel{ mainFrame, wxID_ANY, wxPoint{-1, -1}, wxSize{BrickElementsWidth, BrickElementsHeight} },
	selectedBrick{ bricks::index::GenericBrick, bricks::GenericBrick::Blue },
	position{ BrickElementsWidth / 2 - SQR_SIZE / 2, BrickElementsHeight / 2 - SQR_SIZE / 2 },
	tex{bricksTextures}
{
	Connect(wxEVT_PAINT, wxPaintEventHandler(SelectedBrickPanel::drawSelectedBrick ) );
}

const BrickData& SelectedBrickPanel::getBrick() const
{
	return selectedBrick;
}

BrickData& SelectedBrickPanel::getBrick()
{
	return selectedBrick;
}

void SelectedBrickPanel::setSelectedBrick(unsigned index, unsigned property)
{
	selectedBrick.set(index, property);
	Refresh();
}

void SelectedBrickPanel::previousCategory()
{
	if( selectedBrick.index > 1 )
	{
		selectedBrick.index--;
		selectedBrick.property = 0;
		Refresh();
	}
}

void SelectedBrickPanel::nextCategory()
{
	if( selectedBrick.index < tex.getSize() )
	{
		selectedBrick.index++;
		selectedBrick.property = 0;
		Refresh();
	}
}

void SelectedBrickPanel::previousSubCategory()
{
	assert( selectedBrick.index < bricks::index::Max );
	if( selectedBrick.property > 0 )
	{
		selectedBrick.property--;
		Refresh();
	}
}

void SelectedBrickPanel::nextSubCategory()
{
	assert( selectedBrick.index < bricks::index::Max );
	if( selectedBrick.property + 1 < tex.getCategorySize(selectedBrick) )
	{
		selectedBrick.property++;
		Refresh();
	}
}

void SelectedBrickPanel::drawSelectedBrick(wxPaintEvent& paintEvent)
{
	wxPaintDC drawingContext{this};
	tex.drawSingleBrick(drawingContext, selectedBrick, position);
}