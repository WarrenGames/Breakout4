#include "contexts/gameStarting/setupFiles/setupLanguageFile.h"
#include "fileSystem/copyFilesAndDirectories.h"
#include "fileSystem/createNewElementFs.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texts/textLoader.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"
#include "contexts/gameStarting/initWindowAndRenderer/initWindowRenderer.h"
#include "consts/constPaths.h"

void setupFiles::createMainLanguageDirectory(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	if( createFs::FsNewError != createFs::mkDirectoryIfMissing( prefPath.getPath(), DestinationLanguageDirectory ) )
	{
		setupFiles::createMainLanguageFile(logs, prefPath);
	}
	else{
		logs.error.wrFileOpeningError(DestinationLanguageDirectory, "create a directory");
	}
}

void setupFiles::createMainLanguageFile(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	if( copyFs::FsCopyError != copyFs::fileWithLogNoErase(logs, MainLanguageFilePath, path::getChosenLangFile(prefPath, ChosenLanguageFileName) )
		&& copyFs::FsCopyError != copyFs::fileWithLogNoErase(logs, LanguagesEnumFilePath, path::getChosenLangFile(prefPath, LanguagesEnumFileName) ) )
	{
		setupFiles::loadLanguage(logs, prefPath);
	}
	else{
		logs.error.wrPrefix();
		logs.error.wrStringNoEndline("failed to copy 'chosen language' and/or 'languages enum' files to pref path: ");
		logs.error.wrStringNoEndline(prefPath.getPath() );
		logs.error.wrEndLine();
	}
}

void setupFiles::loadLanguage(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	if( const TextsBlocks langLoading{logs.error, path::getChosenLangFile(prefPath, ChosenLanguageFileName), 1} )
	{
		cntxt::windRend::create(logs, prefPath, langLoading[0]);
	}
	else{
		logs.error.wrPrefixAndSimpleMessage("failed to load the language for the 'breakout4' game.");
	}
}