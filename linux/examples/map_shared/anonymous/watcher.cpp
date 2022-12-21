#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>

int main() {
	char name[] = "/shm_object";
	int fd = shm_open(name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (fd < 0) {
		std::cout << "failed to shm" << std::endl;
		return -1;
	}
	size_t size = 8;
	if (ftruncate(fd, size) < 0) {
		std::cout << "failed to ftruncate" << std::endl;
		return -1;
	}
    char* map = (char *)mmap(NULL,
                        size, // how many bytes to read
                        PROT_READ, MAP_FILE|MAP_SHARED, /*flags*/ fd, /*file*/ 
                        0 // offset
						);
	std::cout << "map address: " << &map << std::endl;
	std::cout << map << std::endl;
	char* copy = (char*) malloc(size);
	strcpy(copy, map);
	bool mismatch = false;
	while (not mismatch) {
		for (int i = 0; i < size / sizeof(char); i++)
			if (copy[i] != map[i])
				mismatch = true;
	}
	std::cout << "mismatch detected" << std::endl;
	std::cout << map << std::endl;
	if (shm_unlink(name) < 0) {
		std::cout << "failed to unlink" << std::endl;
		return -1;
	}
	return 0;
}
