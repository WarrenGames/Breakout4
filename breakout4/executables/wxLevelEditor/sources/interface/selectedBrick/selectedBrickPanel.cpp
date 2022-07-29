#include "interface/selectedBrick/selectedBrickPanel.h"
#include "interface/mainLayout/mainFrame.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/constexprScreen.h"
#include "wx/dcclient.h"

SelectedBrickPanel::SelectedBrickPanel(MainFrame *mainFrame, OnePBricksTextures& bricksTextures):
	wxPanel{ mainFrame, wxID_ANY, wxPoint{-1, -1}, wxSize{BRICK_ELEMENTS_WIDTH, BRICK_ELEMENTS_HEIGHT} },
	selectedBrick{ BRICKS::INDEX::GEN_BRICK, BRICKS::GENERIC::BLUE },
	position{ BRICK_ELEMENTS_WIDTH / 2 - SQR_SIZE / 2, BRICK_ELEMENTS_HEIGHT / 2 - SQR_SIZE / 2 },
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

void SelectedBrickPanel::drawSelectedBrick(wxPaintEvent& paintEvent)
{
	wxPaintDC drawingContext{this};
	tex.drawSingleBrick(drawingContext, selectedBrick, position);
}