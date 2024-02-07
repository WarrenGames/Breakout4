#ifndef SETUP_CONFIG_FILES_H
#define SETUP_CONFIG_FILES_H

class PrefPathFinder;
struct AppLogFiles;

namespace setupFiles{
	void copyConfigFilesDirectory(AppLogFiles& logs, const PrefPathFinder& prefPath);
}

#endif //SETUP_CONFIG_FILES_H