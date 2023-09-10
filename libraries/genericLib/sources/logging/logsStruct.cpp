#include "logging/logsStruct.h"

constexpr char ErrorPrefix[] = "Error: ";
constexpr char WarningPrefix[] = "Warning: ";

AppLogFiles::AppLogFiles(const fs::path& path, const fs::path& errFile, const fs::path& warnFile):
	error{ path, errFile, ErrorPrefix},
	warning{ path, warnFile, WarningPrefix}
{

}

AppLogFiles::operator bool() const
{
	return error && warning;
}

void AppLogFiles::openFiles(const fs::path& path, const fs::path& errFile, const fs::path& warnFile)
{
	error.openFile(path, errFile, ErrorPrefix);
	warning.openFile(path, warnFile, WarningPrefix);
}