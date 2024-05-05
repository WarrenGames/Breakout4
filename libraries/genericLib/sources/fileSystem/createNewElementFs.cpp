#include "fileSystem/createNewElementFs.h"
#include <fstream>

unsigned createFs::mkDirectoryIfMissing(const fs::path& baseDir, const fs::path& newDir)
{
	if( !fs::exists(baseDir / newDir) )
	{
		std::error_code errorCode;
		if( fs::create_directory(baseDir / newDir, errorCode) )
			return createFs::FsNewCreated;
		else{
			return createFs::FsNewError;
		}
	}
	else{
		return createFs::FsNewExists;
	}
}

unsigned createFs::mkNewFileIfMissing(const fs::path& fileDirectory, const fs::path& fileName)
{
	if( !fs::exists(fileDirectory / fileName) )
	{
		if( std::ofstream newFile{ fileDirectory / fileName } )
			return FsNewCreated;
		else
			return createFs::FsNewError;
	}
	else{
		return createFs::FsNewExists;
	}
}

unsigned createFs::mkNewFileIfMissing(const fs::path& fileFullPath)
{
	if( !fs::exists(fileFullPath) )
	{
		if( std::ofstream newFile{ fileFullPath } )
			return FsNewCreated;
		else
			return createFs::FsNewError;
	}
	else{
		return createFs::FsNewExists;
	}
}