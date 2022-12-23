#include <windows.h> 
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <system_error>
#include <tchar.h>
#include <shlobj.h>
#include <cstdio>
#include <strsafe.h>
#include <string.h>


#define BUF_SIZE 1024

#define PIPE_BUF_SIZE 65536

#define SHM_ERROR           8388608
#define NOT_SETUP           4194304
#define FAILED_TO_MAP         65536
#define FAILED_TO_CREATE     131072
#define FAILED_TO_OPEN       262144
#define FAILED_TO_DISCONNECT 524288
#define BAD_WRITE           1048576
#define BAD_READ            2097152 
#define SUCCESS 0

using namespace std;

namespace pipc {
	class shmem {
		private:
			CHAR* shm_name;
			DWORD shm_flag;
			BOOL shm_create;
			size_t shm_size;
			HANDLE shm_handle;
			CHAR* map;
			BOOL issetup = false;

		public:
			shmem(CHAR* name, size_t size, BOOL create, DWORD openMode)
			: shm_name(name), shm_size(size), shm_create(create), shm_flag(openMode)
			{ }
			int setup() {
				if (shm_create) {
					shm_handle = CreateFileMappingA(
										INVALID_HANDLE_VALUE,
										NULL, // read/write permission
										PAGE_READWRITE,
										0,
										shm_size,
										shm_name);
					if (shm_handle == NULL) {
						std::cout << "failed to create" << std::endl;
						return SHM_ERROR | FAILED_TO_CREATE;
					}
				} else {
					shm_handle = OpenFileMappingA(shm_flag,
												FALSE,
												shm_name);
				    if (shm_handle == NULL)
						return SHM_ERROR | FAILED_TO_OPEN;
				}
				map = (CHAR*) MapViewOfFile(shm_handle,   // handle to map object
											   shm_flag, // read/write permission
											   0,
											   0,
											   shm_size);
				if (map == NULL) {
					std::cout << "failed to map" << std::endl;
					return SHM_ERROR | FAILED_TO_MAP;
				}
				issetup = true;
				return SUCCESS;
			}

			int read_shm(CHAR* buf, size_t n) {
				if (!issetup)
					return SHM_ERROR | NOT_SETUP;
				CopyMemory(buf, map, n);
				return SUCCESS;
			}

			int write_shm(CHAR* buf, size_t n) {
				if (!issetup)
					return SHM_ERROR | NOT_SETUP;
				CopyMemory(map, buf, n);
				return SUCCESS;
			}

			~shmem() {
				if (shm_create)
					DisconnectNamedPipe(shm_handle);
				else
					CloseHandle(shm_handle);
			}
	};
}


