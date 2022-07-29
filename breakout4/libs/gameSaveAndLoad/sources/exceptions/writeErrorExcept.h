#ifndef WRITE_ERROR_EXCEPT_H
#define WRITE_ERROR_EXCEPT_H

#include <stdexcept>
#include <string>

class WriteError : public std::runtime_error
{

public:
	explicit WriteError(const std::string& whatArg);
};

#endif //WRITE_ERROR_EXCEPT_H