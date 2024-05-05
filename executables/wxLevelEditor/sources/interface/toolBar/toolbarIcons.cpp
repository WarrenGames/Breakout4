#include "interface/toolBar/toolbarIcons.h"
#include "consts/buttonEventsID.h"
#include <wx/frame.h>
#include <wx/string.h>
#include <cassert>

constexpr char ShiftDownIconPath[] = "textures/editor/toolbar/shiftDownButton.png";
constexpr char ShiftUpIconPath[] = "textures/editor/toolbar/shiftUpButton.png";

enum{	BrickSelectCategoryPrevious,
		BrickSelectCategoryNext,
		BrickSelectSubCategoryPrevious,
		BrickSelectSubCategoryNext,
		BrickSelectMax };

ToolbarIcons::ToolbarIcons(wxFrame *frame):
	shiftUpIcon{ShiftUpIconPath, wxBITMAP_TYPE_PNG},
	shiftDownIcon{ShiftDownIconPath, wxBITMAP_TYPE_PNG},
	bricksSelectorIcons{ 
		wxBitmap{ "textures/editor/toolbar/categoryMinus.png", wxBITMAP_TYPE_PNG },
		wxBitmap{ "textures/editor/toolbar/categoryPlus.png", wxBITMAP_TYPE_PNG },
		wxBitmap{ "textures/editor/toolbar/subCatMinus.png", wxBITMAP_TYPE_PNG },
		wxBitmap{ "textures/editor/toolbar/subCatPlus.png", wxBITMAP_TYPE_PNG }
	},
	toolbar{ new wxToolBar{ frame, wxID_ANY } }
{
	assert( shiftUpIcon.IsOk() );
	assert( shiftDownIcon.IsOk() );
	
	if( toolbar )
	{
		toolbar->AddTool( toolbarIcons::ShiftUpId, wxString{"Shift up grid"}, shiftUpIcon, wxString{"Shift up grid"} );
		toolbar->AddTool( toolbarIcons::ShiftDownId, wxString{"Shift down grid"}, shiftDownIcon, wxString{"Shift down grid"} );
		
		toolbar->AddTool( toolbarIcons::CatPrevious, wxString{"Previous brick category"}, bricksSelectorIcons[BrickSelectCategoryPrevious], wxString{"Previous brick category"} );
		toolbar->AddTool( toolbarIcons::CatNext, wxString{"Next brick category"}, bricksSelectorIcons[BrickSelectCategoryNext], wxString{"Next brick category"} );
		toolbar->AddTool( toolbarIcons::SubCatPrevious, wxString{"Previous brick sub-category"}, bricksSelectorIcons[BrickSelectSubCategoryPrevious], wxString{"Previous brick sub-category"} );
		toolbar->AddTool( toolbarIcons::SubCatNext, wxString{"Next brick sub-category"}, bricksSelectorIcons[BrickSelectSubCategoryNext], wxString{"Next brick sub-category"} );
		
		toolbar->Realize();
	}
}