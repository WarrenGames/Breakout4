#include "logging/logsStruct.h"

constexpr char ErrorPrefix[] = "Error: ";
constexpr char WarningPrefix[] = "Warning: ";

AppLogFiles::AppLogFiles(const std::string& path, const std::string& errFile, const std::string& warnFile):
	error{ path, errFile, ErrorPrefix},
	warning{ path, warnFile, WarningPrefix}
{

}

AppLogFiles::operator bool() const
{
	return error && warning;
}

void AppLogFiles::openFiles(const std::string& path, const std::string& errFile, const std::string& warnFile)
{
	error.openFile(path, errFile, ErrorPrefix);
	warning.openFile(path, warnFile, WarningPrefix);
}