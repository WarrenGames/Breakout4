#include "interface/toolBar/fileMenuComponents.h"

FileMenuComponents::FileMenuComponents():
	file{ new wxMenu }
{
	fileComponents.emplace_back( new wxMenuItem{ file, fileHandling::OpenFile, wxT("Open 'One player' grid file") } );
	fileComponents.emplace_back( new wxMenuItem{ file, fileHandling::SaveFileAs, wxT("Save as 'One player' grid file") } );
	fileComponents.emplace_back( new wxMenuItem{ file, fileHandling::SaveToSameFile, wxT("Save 'one player grid' to same file") } );
	
	appendMenuItems();
}

void FileMenuComponents::appendMenuItems()
{
	for( auto &item : fileComponents )
	{
		file->Append( item );
	}
}