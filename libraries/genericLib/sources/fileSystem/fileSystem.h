#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H


#if( __GNUG__ >= 8 )
	#include <filesystem>
	namespace fs = std::filesystem;
#elif( __GNUG__ == 7 )
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#elif( _MSC_VER >= 1910 )
	#include <filesystem> // Microsoft-specific implementation header file name
	namespace fs = std::filesystem;
#else
	#include <filesystem>
	namespace fs = std::filesystem;
#endif

#endif//FILE_SYSTEM_H