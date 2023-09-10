#ifndef SELECTED_BRICK_PANEL_H
#define SELECTED_BRICK_PANEL_H

#include "interface/currentGrid/onePlayerGrid/brickData.h"
#include "interface/currentGrid/onePlayerGrid/bricksTextures.h"
#include "customTypes/positionTypes.h"
#include "wx/panel.h"
#include <vector>

class MainFrame;

class SelectedBrickPanel : public wxPanel
{
private:
	BrickData selectedBrick;
	Offset position;
	OnePBricksTextures& tex;
	std::vector< unsigned > propertiesMax;
	
public:
	explicit SelectedBrickPanel(MainFrame *mainFrame, OnePBricksTextures& bricksTextures);
	~SelectedBrickPanel() = default;
	SelectedBrickPanel( const SelectedBrickPanel& ) = delete;
	SelectedBrickPanel& operator= ( const SelectedBrickPanel& ) = delete;
	
	const BrickData& getBrick() const;
	BrickData& getBrick();
	void setSelectedBrick(unsigned index, unsigned property);
	void previousCategory();
	void nextCategory();
	void previousSubCategory();
	void nextSubCategory();
	
private:
	void drawSelectedBrick(wxPaintEvent& paintEvent);
};

#endif //SELECTED_BRICK_PANEL_H