#include "fileSystem/copyFilesAndDirectories.h"
#include "logging/logsStruct.h"

unsigned copyFs::fileWithLogNoErase(AppLogFiles& logs, const fs::path& srcFilePath, const fs::path& destFilePath)
{
	if( false == fs::exists(destFilePath) )
	{
		if( fs::exists(srcFilePath) )
		{
			std::error_code errorCode;
			if( fs::copy_file(srcFilePath, destFilePath, errorCode) )
			{
				logs.warning.wrSimpleMessage("Copying file: " + srcFilePath.string() + " to " + destFilePath.string() + " done with success");
				return copyFs::FsCopyCreated;
			}
			else{
				logs.error.wrPrefixAndSimpleMessage("couldn't copy '" + srcFilePath.string() + "' to '" + destFilePath.string() + "' because " + errorCode.message() );
				return copyFs::FsCopyError;
			}
		}
		else{
			logs.error.wrPrefixAndSimpleMessage("the source file: '" + srcFilePath.string() + "' doesn't exist. Reinstall that file to carry on.");
			return copyFs::FsCopyError;
		}
	}
	else{
		return copyFs::FsCopyExists;
	}
}

void copyFs::directoriesRecursively(AppLogFiles& logs, const fs::path& srcPath, const fs::path& destPath)
{
	if( false == fs::exists( destPath ) )
	{
		logs.warning.wrSimpleMessage("Info: Copying '" + srcPath.string() + "' directory to " + destPath.string());
		std::error_code errorCode;
		fs::copy(srcPath, destPath, fs::copy_options::recursive, errorCode);
		if( errorCode )
		{
			logs.error.wrRessourceCreationError(srcPath.string() + " to " + destPath.string(), errorCode.message() );
		}
	}
	else{
		logs.warning << "The directory '" << destPath.string() << "' already exists, so the files in the '" << srcPath.string() << "' directory are not copied recursively.\n";
	}
}