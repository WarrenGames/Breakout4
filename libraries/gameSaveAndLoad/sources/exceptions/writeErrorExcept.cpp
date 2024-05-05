#include "exceptions/writeErrorExcept.h"

WriteError::WriteError(const std::string& whatArg):
	std::runtime_error{whatArg}
{
	
}