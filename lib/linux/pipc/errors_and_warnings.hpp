#ifndef ERROR_WARNING_HEADER
#define ERROR_WARNING_HEADER

#include <vector>
#include <string>
#include <iostream>

#define PROCESS_ERROR 32768    // 1000 0000  0000 0000
#define FILE_ERROR 16384       // 0100 0000  0000 0000
#define PIPE_ERROR 8192        // 0010 0000  0000 0000
#define FORWARD_ERROR 4096     // 0001 0000  0000 0000
#define ARGUMENT_ERROR 2048    // 0000 1000  0000 0000
#define PROCESS_FAILED 256     // 0000 0001  1000 0000
#define FAILED_TO_FORK 1       // 0000 0000  0000 0001
#define FAILED_TO_OPEN 2       // 0000 0000  0000 0010
#define INVALID_FD 4           // 0000 0000  0000 0100
#define INVALID_FD_FLAG 8      // 0000 0000  0000 1000
#define FAILED_TO_PIPE 16      // 0000 0000  0001 0000
#define FAILED_TO_DUP 32       // 0000 0000  0010 0000
#define FAILED_TO_CLOSE 64     // 0000 0000  0100 0000

#define NOT_SETUP          4194304

#define FAILED_TO_UNLINK   1048576

#define FIFO_ERROR         8388608

#define FAILED_TO_MKFIFO     65536

#define SHM_ERROR          8388608

#define FAILED_TO_MMAP      131072
#define FAILED_TO_MUNMAP    262144
#define FAILED_TO_FTRUNCATE 524288

#define OUT_OF_BOUNDS      2097152

#define BAD_WRITE           524288
#define BAD_READ           1048576

#define SUCCESS 0


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