#ifndef LOGS_STRUCTS_H
#define LOGS_STRUCTS_H

#include "logging/logFile.h"

struct AppLogFiles
{
	LogFile error;
	LogFile warning;
	
	explicit AppLogFiles() = default;
	explicit AppLogFiles(const fs::path& path, const fs::path& errFile, const fs::path& warnFile);
	~AppLogFiles() = default;
	AppLogFiles( const AppLogFiles& ) = delete;
	AppLogFiles& operator= ( const AppLogFiles& ) = delete;
	AppLogFiles( AppLogFiles&& ) = default;
	AppLogFiles& operator= ( AppLogFiles&& ) = default;
	
	operator bool() const;
	void openFiles(const fs::path& path, const fs::path& errFile, const fs::path& warnFile);
};

#endif //LOGS_STRUCTS_H