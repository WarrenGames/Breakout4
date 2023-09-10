#ifndef TOOL_BAR_FILE_MENU_COMPONENTS_H
#define TOOL_BAR_FILE_MENU_COMPONENTS_H

#include "wx/menuitem.h"
#include "wx/menu.h"
#include <vector>

namespace fileHandling{
	constexpr int OpenFile = 201;
	constexpr int SaveFileAs = 202;
	constexpr int SaveToSameFile = 203;
}

struct FileMenuComponents
{
	wxMenu *file;
	std::vector< wxMenuItem* > fileComponents;
	
	FileMenuComponents();
	~FileMenuComponents() = default;
	FileMenuComponents( const FileMenuComponents& ) = delete;
	FileMenuComponents& operator= ( const FileMenuComponents& ) = delete;
	FileMenuComponents( FileMenuComponents&& ) = default;
	FileMenuComponents& operator= ( FileMenuComponents&& ) = default;
	void appendMenuItems();
};

#endif //TOOL_BAR_FILE_MENU_COMPONENTS_H