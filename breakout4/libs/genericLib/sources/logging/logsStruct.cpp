#include "logging/logsStruct.h"

constexpr char ERROR_PREFIX[] = "Error: ";
constexpr char WARNING_PREFIX[] = "Warning: ";

AppLogFiles::AppLogFiles(const std::string& path, const std::string& errFile, const std::string& warnFile):
	error{ path, errFile, ERROR_PREFIX},
	warning{ path, warnFile, WARNING_PREFIX}
{

}

AppLogFiles::operator bool() const
{
	return error && warning;
}

void AppLogFiles::openFiles(const std::string& path, const std::string& errFile, const std::string& warnFile)
{
	error.openFile(path, errFile, ERROR_PREFIX);
	warning.openFile(path, warnFile, WARNING_PREFIX);
}