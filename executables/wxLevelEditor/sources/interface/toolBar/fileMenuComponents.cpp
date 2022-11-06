#include "interface/toolBar/fileMenuComponents.h"

FileMenuComponents::FileMenuComponents():
	file{ new wxMenu }
{
	fileComponents.emplace_back( new wxMenuItem{ file, fileHandling::OpenFile, wxT("Open 'One player' grid file") } );
	fileComponents.emplace_back( new wxMenuItem{ file, fileHandling::SaveFile, wxT("Save 'One player' grid file") } );
	
	appendMenuItems();
}

void FileMenuComponents::appendMenuItems()
{
	for( auto &item : fileComponents )
	{
		file->Append( item );
	}
}