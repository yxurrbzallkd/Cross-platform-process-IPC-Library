#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main() {
	const char* file = "file.txt";
	int fd = open(file, O_RDWR);
	if (fd < 0) // file opened correctly?
		return -1;
	struct stat sb;
	if (fstat(fd, &sb) == -1) // get file stats successfull?
		return -1;
    size_t filesize = sb.st_size;
    char* map = (char *)mmap(NULL,
                        filesize, // how many bytes to read
                        PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, /*flags*/ -1, /*anonymous file*/ 
                        0 // offset
						);
	if (close(fd) < 0) return -1;
	std::cout << "map address: " << &map << std::endl;
	std::cout << map << std::endl;
	return 0;
}
