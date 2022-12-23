#include <stdio.h>
#include <iostream>
#include "shmem.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	std::cout << "creating a shm" << std::endl;
	pipc::shmem s("Local\\ShmObject", 1024, TRUE, FILE_MAP_READ | FILE_MAP_WRITE);
	if (s.setup() != SUCCESS)
		return -1;
	char msg[] = "hello world!";
	std::cout << "writing " << msg << " result " << s.write_shm(msg, 13) << std::endl;
	char content[1025];
	std::cout << "reading, result " << s.read_shm(content, 1024);
	//content[1024] = '\0';
	std::cout << " read " << content << std::endl;
	return 0;
}
