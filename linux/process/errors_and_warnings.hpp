#ifndef ERROR_WARNING_HEADER
#define ERROR_WARNING_HEADER

#include <vector>
#include <string>
#include <iostream>

int error_return(std::string message) {
	int errcode = errno;
	std::cerr << "ERROR: " << message << std::endl;
	return errcode;
}

int error_exit(std::string message) {
	perror(message.c_str());
	exit(errno);
}

void warn(std::string warning) {
	std::cerr << "WARNING: " << warning << std::endl;
}

#endif