#include "time/dateAndTime.h"
#include <mutex>

constexpr std::size_t DateStringSize = 128;

std::tm localtime_safe(std::time_t timer)
{
	std::tm bt{};
	#if defined (__unix__ )
		localtime_r(&timer, &bt);
	#elif defined (_MSC_VER )
		localtime_s(&bt, &timer);
	#else
		static std::mutex mtx;
		std::lock_guard< std::mutex > lock( mtx );
		bt = * std::localtime(&timer);
	#endif 
		return bt;
}

std::string returnCurrentTimeAndDate()
{
	auto bt = localtime_safe( std::time( nullptr ) );
	char formattedTimeString[DateStringSize];
	
	if( std::strftime(formattedTimeString, DateStringSize, "%Y-%m-%d time: %H:%M", &bt ) )
	{
		return std::string{formattedTimeString};
	}
	else{
		return std::string{"Date string creation error"};
	}
}

std::string returnCurrentDate()
{
	auto bt = localtime_safe( std::time( nullptr ) );
	char formattedTimeString[DateStringSize];
	
	if( std::strftime(formattedTimeString, DateStringSize, "%Y-%m-%d", &bt ) )
	{
		return std::string{formattedTimeString};
	}
	else{
		return std::string{"Date string creation error"};
	}
}