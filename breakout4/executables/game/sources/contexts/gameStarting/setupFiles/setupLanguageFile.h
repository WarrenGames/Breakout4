#ifndef SETUP_LANGUAGE_FILE_H
#define SETUP_LANGUAGE_FILE_H

class PrefPathFinder;
struct AppLogFiles;

namespace setupFiles{
	void createMainLanguageDirectory(AppLogFiles& logs, const PrefPathFinder& prefPath);
	
	void createMainLanguageFile(AppLogFiles& logs, const PrefPathFinder& prefPath);
	
	void loadLanguage(AppLogFiles& logs, const PrefPathFinder& prefPath);
}

#endif //SETUP_LANGUAGE_FILE_H