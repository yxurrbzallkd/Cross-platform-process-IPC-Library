#include <windows.h> 
#include <iostream>
#include <string>
#include <shlobj.h>
#include <conio.h>
#include <cstdio>
#include <strsafe.h>
#include <string.h>

using namespace std;
#define BUF_SIZE 65536

int main(int argc, char* argv[]) {
	CHAR* name = "Local\\MyFileMappingObject";
	CHAR* programPath = "./t.exe";
	if (argc == 1) {
		// parent
		HANDLE hMap = CreateFileMappingA(
										INVALID_HANDLE_VALUE,
										NULL, // read/write permission
										PAGE_READWRITE,
										0,
										BUF_SIZE,
										name);
		if (hMap == NULL)
			return GetLastError();
		
		CHAR* pBuf = (CHAR*) MapViewOfFile(hMap,   // handle to map object
									   FILE_MAP_READ, // read/write permission
									   0,
									   0,
									   BUF_SIZE);
		if (pBuf == NULL) {
			DWORD err = GetLastError();
			CloseHandle(hMap);
			return err;
		}

		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;
		ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
		ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
		siStartInfo.cb = sizeof(STARTUPINFO);

		std::string s = std::string(programPath)+" 0";
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
			return GetLastError();
		WaitForSingleObject(piProcInfo.hProcess, INFINITE);

		CHAR buf[1024];
		CopyMemory(buf, pBuf, 1024);
		std::cout << pBuf << std::endl;
		UnmapViewOfFile(pBuf);
		CloseHandle(hMap);
	} else {
		// child
		HANDLE hFile = OpenFileMappingA(FILE_MAP_WRITE,
										FALSE,
										name);
		if (hFile == NULL)
			return GetLastError();
		CHAR* pBuf = (CHAR*) MapViewOfFile(hFile,   // handle to map object
									   FILE_MAP_WRITE, // read/write permission
									   0,
									   0,
									   BUF_SIZE);
		if (pBuf == NULL)
			return GetLastError();
		
		char buf[] = "Hello World!";
		CopyMemory((PVOID)pBuf, buf, 1024);
		UnmapViewOfFile(pBuf);
		CloseHandle(hFile);
	}
	return 0;
}

