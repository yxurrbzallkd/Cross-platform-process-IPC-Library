#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>

int main(int argc, char* argv[]) {
	char name[] = "/shm_object";
	int fd = shm_open(name, W_OK, S_IRUSR|S_IWUSR);
	if (fd < 0) {
		std::cout << "failed to shm" << std::endl;
		return -1;
	}
	size_t size = 8;
    char* map = (char *)mmap(NULL,
                        size, // how many bytes to read
                        PROT_WRITE, MAP_FILE|MAP_SHARED, /*flags*/ fd, /*file*/ 
                        0 // offset
						);
	if (argc == 1)
		strcpy(map, "hi Diana");
	else
		strcpy(map, argv[1]);
	if (munmap(map, size) < 0) {
		std::cout << "failed to munmap" << std::endl;
		return -1;
	}
	return 0;
}
