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
	if( FS_NEW_ERROR != createFs::mkDirectoryIfMissing( prefPath.getPath(), DEST_LANG_DIR ) )
	{
		setupFiles::createMainLanguageFile(logs, prefPath);
	}
	else{
		logs.error.wrFileOpeningError(DEST_LANG_DIR, "create a directory");
	}
}

void setupFiles::createMainLanguageFile(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	if( FS_COPY_ERROR != copyFs::fileWithLogNoErase(logs, MAIN_LANGFILE_PATH, path::getChosenLangFile(prefPath, CHOSEN_LANG_FILENAME) )
		&& FS_COPY_ERROR != copyFs::fileWithLogNoErase(logs, LANGUAGES_ENUM, path::getChosenLangFile(prefPath, LANGUAGES_ENUM_FILENAME) ) )
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
	const TextsBlocks langLoading{logs.error, path::getChosenLangFile(prefPath, CHOSEN_LANG_FILENAME), 1};
			
	if( langLoading.wasReadingPerfect() )
	{
		cntxt::windRend::create(logs, prefPath, langLoading[0]);
	}
	else{
		logs.error.wrPrefixAndSimpleMessage("failed to load the language for the 'breakout4' game.");
	}
}