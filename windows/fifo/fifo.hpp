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

#define FIFO_ERROR          8388608
#define NOT_SETUP           4194304
#define FAILED_TO_CREATEPIPE  65536
#define FAILED_TO_CREATEFILE 131072
#define FAILED_TO_CONNECT    262144
#define FAILED_TO_DISCONNECT 524288
#define BAD_WRITE           1048576
#define BAD_READ            2097152 
#define SUCCESS 0

using namespace std;

namespace pipc {
	class fifo {
		private:
			CHAR* fifo_name;
			DWORD fifo_mode;
			BOOL fifo_create;
			HANDLE fifo_handle;
			BOOL issetup = false;

		public:
			fifo(CHAR* name) : fifo_name(name) {
				fifo_create = true;
			}
			fifo(CHAR* name, DWORD openMode) : fifo_name(name), fifo_mode(openMode) {
				fifo_create = false;
			}
			int setup() {
				if (fifo_create) {
					fifo_handle = CreateNamedPipeA(fifo_name,
													PIPE_ACCESS_DUPLEX,
													PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
							                        1,
							                        1024 * 16,
							                        1024 * 16,
							                        NMPWAIT_USE_DEFAULT_WAIT,
							                        NULL);
					if (fifo_handle == INVALID_HANDLE_VALUE)
						return FIFO_ERROR | FAILED_TO_CREATEPIPE;
				} else {
					fifo_handle = CreateFileA(fifo_name, 
						                       fifo_mode,
						                       0,
						                       NULL,
						                       OPEN_EXISTING,
						                       0,
						                       NULL);
				    if (fifo_handle == INVALID_HANDLE_VALUE)
						return FIFO_ERROR | FAILED_TO_CREATEFILE;
				}
				issetup = true;
				return SUCCESS;
			}

			int read_fifo(CHAR* buf, size_t n, DWORD& dwRead) {
				if (!issetup)
					return FIFO_ERROR | NOT_SETUP;
				if (fifo_create)
					if (!ConnectNamedPipe(fifo_handle, NULL))
						return FIFO_ERROR | FAILED_TO_CONNECT;
				if (!ReadFile(fifo_handle, buf, n, &dwRead, NULL))
					return FIFO_ERROR | BAD_READ;
				if (fifo_create)
					DisconnectNamedPipe(fifo_handle);
				return SUCCESS;
			}

			int write_fifo(CHAR* buf, size_t n,  DWORD& dwWritten) {
				if (!issetup)
					return FIFO_ERROR | NOT_SETUP;
				if (fifo_create)
					if (!ConnectNamedPipe(fifo_handle, NULL))
						return FIFO_ERROR | FAILED_TO_CONNECT;
				if (!WriteFile(fifo_handle, buf, n, &dwWritten, NULL))
					return FIFO_ERROR | BAD_WRITE;
				if (fifo_create)
					DisconnectNamedPipe(fifo_handle);
				return SUCCESS;
			}

			~fifo() {
				if (fifo_create)
					DisconnectNamedPipe(fifo_handle);
				else
					CloseHandle(fifo_handle);
			}
	};
}

