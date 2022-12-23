#include <windows.h> 
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tchar.h>
#include <shlobj.h>
#include <cstdio>
#include <strsafe.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
	CHAR* name = "\\\\.\\pipe\\Pipe";
	CHAR* programPath = "./t.exe";
	if (argc == 1) {
		std::cout << "parent" << std::endl;
		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;
		ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
		ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
		siStartInfo.cb = sizeof(STARTUPINFO);
		DWORD dwRead;
		std::cout << "creating a pipe" << std::endl;
		HANDLE hPipe = CreateNamedPipeA(name,
										PIPE_ACCESS_DUPLEX,
										PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
				                        1,
				                        1024 * 16,
				                        1024 * 16,
				                        NMPWAIT_USE_DEFAULT_WAIT,
				                        NULL);
		std::string s = std::string(programPath)+" 0";
		std::cout << "creating child " << s << std::endl;
		BOOL bSuccess = CreateProcessA(NULL,
									   (char*)s.c_str(),	// command line
									   NULL,		// process security attributes
									   NULL,		// primary thread security attributes
									   TRUE,		// handles are inherited
									   0,			// creation flags
									   NULL,		// use parent's environment
									   NULL,		// use parent's current directory
									   &siStartInfo,	// STARTUPINFO pointer
									   &piProcInfo);	// receives PROCESS_INFORMATION
		if (!bSuccess)
			return -1;
		std::cout << "reading" << std::endl;
		CHAR buf[1024];
		while (hPipe != INVALID_HANDLE_VALUE) {
			if (ConnectNamedPipe(hPipe, NULL)) {
				while (ReadFile(hPipe, buf, sizeof(buf), &dwRead, NULL)) {
					buf[dwRead] = '\0';
					std::cout << buf << std::endl;
				}
			}
			DisconnectNamedPipe(hPipe);
			break;
		}
	} else {
		// child
		HANDLE hPipe;
	    DWORD dwWritten;
	    hPipe = CreateFileA(name, 
	                       GENERIC_READ | GENERIC_WRITE, 
	                       0,
	                       NULL,
	                       OPEN_EXISTING,
	                       0,
	                       NULL);
	    if (hPipe == INVALID_HANDLE_VALUE)
			return -1;
	    WriteFile(hPipe,
                  "Hello Pipe\n",
                  12,   // = length of string + terminating '\0' !!!
                  &dwWritten,
                  NULL);
        CloseHandle(hPipe);
	}
	return 0;
}

