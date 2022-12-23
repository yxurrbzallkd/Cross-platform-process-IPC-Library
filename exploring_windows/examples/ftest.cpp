#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>
#include <system_error>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 1)
		return -1;
	char* file = argv[1];
	HANDLE handle = CreateFileA(file,
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_NEW,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	std::cout << (handle == INVALID_HANDLE_VALUE) << std::endl;
	return 0;
}
