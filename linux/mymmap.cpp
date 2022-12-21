#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main() {
	const char* source_file = "in.txt";
	int source_fd = open(source_file, O_RDONLY);
	if (source_fd < 0) // file opened correctly?
		return -1;
	struct stat sb;
	if (fstat(fd, &sb) == -1) // get file stats successfull?
		return -1;
    size_t filesize = sb.st_size;
	// it is enough to map private
    char* in_map = (char *)mmap(NULL,
                        filesize, // how many bytes to read
                        PROT_READ,
						MAP_FILE | MAP_PRIVATE,
						source_fd,
                        0 // offset
						);
	close(source_fd); // can close now

	const char* dest_file = "out.txt";
	int dest_fd = open(dest_file, O_RDWR | O_CREAT);
	if (dest_fd < 0) // file opened correctly?
		return -1;
	if (ftruncate(dest_fd, filesize) < 0)
		return -1;
	// must map shared, so that the kernel carries the output through to the destination
	char* out_map = (char *)mmap(NULL,
                        filesize, // how many bytes to read
                        PROT_READ|PROT_WRITE,
						MAP_FILE | MAP_SHARED,
						dest_fd, /*anonymous file*/ 
                        0 // offset
						);
	close(dest_fd);
	strcpy(in_map, out_map, filesize); // copy data
	munmap(in_map, filesize);
	munmap(out_map, filesize)
	return 0;
}
