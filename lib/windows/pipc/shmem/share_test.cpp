#include <stdio.h>
#include <iostream>
#include "shmem.hpp"

using namespace std;

char programPath[] = "./share_test.exe";
char shmPath[] = "Local\\ShmObject";

BOOL CreateChildProcess(PROCESS_INFORMATION&, STARTUPINFO&);

int main(int argc, char* argv[]) {
	if (argc == 2) {
		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;

		pipc::shmem s(shmPath, 1024, TRUE, FILE_MAP_READ | FILE_MAP_WRITE);
		if (s.setup() != SUCCESS)
			return -1;
		if (!CreateChildProcess(piProcInfo, siStartInfo))
			return -1;
		WaitForSingleObject(piProcInfo.hProcess, INFINITE);

		char content[1025];
		if (s.read_shm(content, 1024) != SUCCESS)
			return -1;
		std::cout << content << std::endl;
		CloseHandle(piProcInfo.hThread);
		CloseHandle(piProcInfo.hProcess);
	} else {
		pipc::shmem s(shmPath, 1024, FALSE, FILE_MAP_WRITE);
		if (s.setup() != SUCCESS)
			return -1;
		char msg[] = "hello world!";
		if (s.write_shm(msg, 13) != SUCCESS)
			return -1;
	}
	return 0;
}

BOOL CreateChildProcess(PROCESS_INFORMATION& piProcInfo, STARTUPINFO& siStartInfo) {
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);
	BOOL bSuccess = CreateProcessA(NULL,
									   programPath,	// command line
									   NULL,		// process security attributes
									   NULL,		// primary thread security attributes
									   TRUE,		// handles are inherited
									   0,			// creation flags
									   NULL,		// use parent's environment
									   NULL,		// use parent's current directory
									   &siStartInfo,	// STARTUPINFO pointer
									   &piProcInfo);	// receives PROCESS_INFORMATION
	return bSuccess;
}
