#include <stdio.h>
#include <iostream>
#include "shmem.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	std::cout << "creating a shm" << std::endl;
	pipc::shmem s("/shm_object", 1024, O_CREAT | O_RDWR, PROT_READ | PROT_WRITE);
	s.setup_shm();
	const char* msg = "hello world!";
	std::cout << "writing " << msg << " result " << s.write_shm(msg, 0) << std::endl;
	char content[1025];
	std::cout << "reading, result " << s.read_shm(content, 2048, 0);
	content[1024] = '\0';
	std::cout << " read " << content << std::endl;
	return 0;
}
