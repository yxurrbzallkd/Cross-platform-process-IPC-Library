#ifndef SHMEM_HEADER
#define SHMEM_HEADER

#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <pipc/errors_and_warnings.hpp>

namespace pipc {
	class shmem {
		private:
			const char* sname;
			int sfd;
			int shm_flag, map_flag;
			char* map;
			size_t file_size;
			bool issetup = false;
		public:
			shmem(const char* name, size_t size, int sflag=O_RDWR, int mflag=PROT_READ | PROT_WRITE)
			: sname(name), shm_flag(sflag), file_size(size), map_flag(mflag) { }

			int setup() {
				sfd = shm_open(sname, shm_flag, S_IRUSR|S_IWUSR);
				if (sfd < 0)
					return SHM_ERROR & FAILED_TO_OPEN;
				if (ftruncate(sfd, file_size) < 0)
					return SHM_ERROR & FAILED_TO_FTRUNCATE;
				map = (char *)mmap(NULL,
		                        file_size, // how many bytes to read
		                        map_flag, MAP_FILE|MAP_SHARED, /*flags*/ sfd, /*file*/ 
		                        0 // offset
								);
				if (map == NULL)
					return SHM_ERROR & FAILED_TO_MMAP;
				issetup = true;
				return SUCCESS;
			}

			int write_shm(const char* buf, size_t offset) {
				if (!issetup)
					return SHM_ERROR & NOT_SETUP;
				if (offset+strlen(buf) > file_size) // no space
					return OUT_OF_BOUNDS;
				strcpy(map + offset, buf);
				if (strcmp(buf, map+offset) != 0) // check correctness
					return BAD_WRITE;
				return SUCCESS;
			}

			int read_shm(char* buf, size_t n, size_t offset) {
				if (!issetup)
					return SHM_ERROR & NOT_SETUP;
				/*if (strlen(buf) < n) {
					std::cout << strlen(buf) << std::endl;
					return OUT_OF_BOUNDS;
				}*/
				if (offset + n > file_size)
					n = file_size - offset;
				strcpy(buf, map+offset);
				return SUCCESS;
			}

			int resize_shm(size_t new_size) {
				if (!issetup)
					return SHM_ERROR & NOT_SETUP;
				if (ftruncate(sfd, new_size) < 0)
					return SHM_ERROR & FAILED_TO_FTRUNCATE;
				if (munmap(map, file_size) < 0)
					return SHM_ERROR & FAILED_TO_MUNMAP;
				char* new_map = (char*)mmap(NULL,
			                        new_size, // how many bytes to read
			                        map_flag, MAP_FILE|MAP_SHARED, /*flags*/ sfd, /*file*/ 
			                        0 // offset
									);
				if (new_map == NULL)
					return SHM_ERROR & FAILED_TO_MMAP;
				map = new_map;
				return SUCCESS;
			}

			int unlink_shm() {
				if (shm_unlink(sname) < 0)
					return SHM_ERROR & FAILED_TO_UNLINK;
				issetup = false;
				return SUCCESS;
			}

			~shmem() {
				//if ( < 0)
				//	shm_unlink(sname);
				if (map != NULL)
					munmap(map, file_size);
				if (!(sfd < 0))
					close(sfd);
			}
	};
}

#endif