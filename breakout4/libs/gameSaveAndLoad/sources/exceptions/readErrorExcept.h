#ifndef READ_ERROR_EXCEPT_H
#define READ_ERROR_EXCEPT_H

#include <stdexcept>
#include <string>

class ReadError : public std::runtime_error
{
public:
	explicit ReadError(const std::string& whatArg);
};

#endif //READ_ERROR_EXCEPT_Hs