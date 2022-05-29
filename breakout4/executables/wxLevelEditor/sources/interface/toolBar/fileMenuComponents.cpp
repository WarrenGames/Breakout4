#include "interface/toolBar/fileMenuComponents.h"

FileMenuComponents::FileMenuComponents():
	file{ new wxMenu }
{
	fileComponents.emplace_back( new wxMenuItem{ file, OPEN_FILE, wxT("Open 'One player' grid file") } );
	fileComponents.emplace_back( new wxMenuItem{ file, SAVE_FILE, wxT("Save 'One player' grid file") } );
	
	appendMenuItems();
}

void FileMenuComponents::appendMenuItems()
{
	for( auto &item : fileComponents )
	{
		file->Append( item );
	}
}