#ifndef LOG_FILE_OBJECT_H
#define LOG_FILE_OBJECT_H

#include <string>
#include <fstream>

class LogFile
{
private:
	std::string fileFullPath;
	std::string prefix;
	std::ofstream log;

public:
	explicit LogFile() = default;
	explicit LogFile(const std::string& path, const std::string& fileName, const std::string& messagesPrefix);
	~LogFile() = default;
	LogFile( const LogFile& ) = delete;
	LogFile& operator= ( const LogFile& ) = delete;
	LogFile( LogFile&& ) = default;
	LogFile& operator= ( LogFile&& ) = default;
	
	void openFile(const std::string& path, const std::string& fileName, const std::string& messagesPrefix);
	operator bool() const;
	
	void wrFileOpeningError(const std::string& filePath, const std::string& fileGoal);
	void wrFileOpeningError(const std::string& filePath, const std::string& fileGoal, const std::string& reason);
	void wrReadErrorMessage(const std::string& filePath, const std::string& dataType);
	void wrReadErrorMessage(const std::string& filePath, const std::string& dataType, unsigned fileLine);
	void wrRessourceCreationError(const std::string& ressourceType, const std::string& reason);
	void wrRessourceInitError(const std::string& ressourceType, const std::string& reason);
	void wrPrefixAndSimpleMessage(const std::string& message);
	void wrSimpleMessage(const std::string& message);
	
	void wrPrefix();
	void wrStringNoEndline(const std::string& message);
	void wrEndLine();
	void wrUint(unsigned uint);
	void wrSizeType(std::size_t size_type);
	
	template< typename T >
	LogFile& operator<< ( const T& data ){ log << data; return *this; }
	void flushLog();
};

#endif //LOG_FILE_OBJECT_H