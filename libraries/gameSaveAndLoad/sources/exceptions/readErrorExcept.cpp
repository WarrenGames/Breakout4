#include "exceptions/readErrorExcept.h"

ReadError::ReadError(const std::string& whatArg):
	std::runtime_error{whatArg}
{
	
}