#include "logging/logFile.h"

LogFile::LogFile(const fs::path& path, const fs::path& fileName, const std::string& messagesPrefix):
	fileFullPath{ path / fileName },
	prefix{ messagesPrefix },
	log{ path / fileName }
{
	
}

void LogFile::openFile(const fs::path& path, const fs::path& fileName, const std::string& messagesPrefix)
{
	fileFullPath = path / fileName;
	prefix = messagesPrefix;
	log.open(path / fileName);
}

LogFile::operator bool() const
{
	if( log )
		return true;
	else
		return false;
}

void LogFile::wrFileOpeningError(const fs::path& filePath, const std::string& fileGoal)
{
	log << prefix << "couldn't open '" << filePath.string() << "' file in order to " << fileGoal << " .\n";
}

void LogFile::wrFileOpeningError(const fs::path& filePath, const std::string& fileGoal, const std::string& reason)
{
	log << prefix << "couldn't open '" << filePath.string() << "' file in order to " << fileGoal << " ; because: " << reason << ".\n";
}

void LogFile::wrReadErrorMessage(const fs::path& filePath, const std::string& dataType)
{
	log << prefix << "couldn't read " << dataType << " in '" << filePath.string() << "' file.\n";
}

void LogFile::wrReadErrorMessage(const fs::path& filePath, const std::string& dataType, unsigned fileLine)
{
	log << prefix << "couldn't read " << dataType << " in '" << filePath.string() << "' file at line " << fileLine << ".\n";
}

void LogFile::wrRessourceCreationError(const std::string& ressourceType, const std::string& reason)
{
	log << prefix << "couldn't create " << ressourceType << " , because: " << reason << " .\n";
}

void LogFile::wrRessourceInitError(const std::string& ressourceType, const std::string& reason)
{
	log << prefix << "couldn't initialize " << ressourceType << " , because: " << reason << " .\n";
}

void LogFile::wrPrefixAndSimpleMessage(const std::string& message)
{
	log << prefix << message << "\n";
}

void LogFile::wrSimpleMessage(const std::string& message)
{
	log << message << "\n";
}

void LogFile::wrPrefix()
{
	log << prefix;
}

void LogFile::wrStringNoEndline(const std::string& message)
{
	log << message;
}

void LogFile::wrEndLine()
{
	log << "\n";
}

void LogFile::wrUint(unsigned uint)
{
	log << uint;
}

void LogFile::wrSizeType(std::size_t size_type)
{
	log << size_type;
}

void LogFile::flushLog()
{
	log.flush();
}