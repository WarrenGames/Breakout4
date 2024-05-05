#ifndef CHEATING_FILE_CHECKING_OUT_H
#define CHEATING_FILE_CHECKING_OUT_H

#include <string>

class PrefPathFinder;

constexpr char OnePlayerCheatFile[] = "onePlayerCheating.ini";

class CheatingFile
{
private:
	bool isCheatActive;
	
public:
	CheatingFile(const PrefPathFinder& prefPath, const std::string& subPath);
	~CheatingFile() = default;
	CheatingFile( const CheatingFile& ) = delete;
	CheatingFile& operator= ( const CheatingFile& ) = delete;
	CheatingFile( CheatingFile&& ) = default;
	CheatingFile& operator= ( CheatingFile&& ) = default;
	
	bool wasFileWithDataFound() const;
	
	void readFile(const std::string& fileFullPath);
};

#endif //CHEATING_FILE_CHECKING_OUT_H