#include <windows.h> 
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include "vector_to_chararr.hpp"
#include "errors_and_warnings.hpp"
#include <typeinfo>	// operator typeid
#include <bitset>
#include <system_error>
#include <tchar.h>
#include "shlobj.h"
#include <cstdio>
#include <strsafe.h>
#include <string.h>

#define BUF_SIZE 1024

using namespace std;

bool _findFile(CHAR* startDirectory, CHAR* fileToFind, CHAR* foundFile, bool recurse) {
	WIN32_FIND_DATAA data;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CHAR pathBuffer[MAX_PATH];

	StringCchPrintfA(pathBuffer, MAX_PATH, startDirectory);
	StringCchCatA(pathBuffer, MAX_PATH, "\\*");
	hFind = FindFirstFileA(pathBuffer, &data);

	if (INVALID_HANDLE_VALUE == hFind)
		return false;
	
	do
	{
		if (strcmp(data.cFileName, fileToFind) == 0) {
			//printf("File found at: %s\n", pathBuffer);
			CHAR newPath[MAX_PATH];
			StringCchPrintfA(newPath, MAX_PATH, startDirectory);
			StringCchCatA(newPath, MAX_PATH, "\\");
			StringCchCatA(newPath, MAX_PATH, data.cFileName);
			StringCchPrintfA(foundFile, MAX_PATH, newPath);
			return true;
		}
		if (recurse && (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			!(data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
			// check for . and .. links
			if ( (strcmp(data.cFileName, ".") != 0) && (strcmp(data.cFileName,  "..") != 0) ) {
				//printf("Found: %s\n", data.cFileName);
				// modify buffer to have it be the starting point for the recursive call
				CHAR newPath[MAX_PATH];
				StringCchPrintfA(newPath, MAX_PATH, startDirectory);
				StringCchCatA(newPath, MAX_PATH, "\\");
				StringCchCatA(newPath, MAX_PATH, data.cFileName);
				if (_findFile(newPath, fileToFind, foundFile, recurse))
					return true;
			}
		}
	}
	while (FindNextFileA(hFind, &data) != 0);
	DWORD dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
	{
		std::cout << "FindNextFile failed" << std::endl;
		return false;
	}
	FindClose(hFind);
	return false;
}

bool findFile(CHAR* fileToFind, CHAR* foundFile) {
	/*
	CHAR pf[MAX_PATH];
	SHGetSpecialFolderPathA(
		 0,
		 pf, 
		 CSIDL_PROGRAM_FILES, 
		 FALSE ); 
	if (_findFile(pf, fileToFind, foundFile, true))
		return true;
	*/
	CHAR windir[MAX_PATH];
	GetWindowsDirectoryA(windir, MAX_PATH);
	if (_findFile(windir, fileToFind, foundFile, false))
		return true;
	StringCchCatA(windir, MAX_PATH, "\\");
	StringCchCatA(windir, MAX_PATH, "System32");
	if (_findFile(windir, fileToFind, foundFile, false))
		return true;
	return false;
}



int main(int argc, char* argv[]) {
	if (argc < 2)
		error_exit("provide argument");
	
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	HANDLE handle_in, handle_out, handle_err;

	handle_in = GetStdHandle(STD_INPUT_HANDLE);
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	handle_err = GetStdHandle(STD_ERROR_HANDLE);

	int res;
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

	if ( ! SetHandleInformation(handle_out, HANDLE_FLAG_INHERIT, 0) )
		error_exit("failed to set handle info on stdout pipe");
	if ( ! SetHandleInformation(handle_in, HANDLE_FLAG_INHERIT, 0) )
		error_exit("failed to set handle info on stdin pipe");
	if ( ! SetHandleInformation(handle_err, HANDLE_FLAG_INHERIT, 0) )
		error_exit("failed to set handle info on stderr pipe");

	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = handle_err;
	siStartInfo.hStdOutput = handle_out;
	siStartInfo.hStdInput = handle_in;
	//siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	HANDLE out;
	HANDLE err;
	BOOL ret = DuplicateHandle( GetCurrentProcess(), GetStdHandle(STD_OUTPUT_HANDLE),  GetCurrentProcess(), &out, 0, TRUE, DUPLICATE_SAME_ACCESS);//todo check ret
	ret = DuplicateHandle( GetCurrentProcess(), GetStdHandle(STD_ERROR_HANDLE),  GetCurrentProcess(), &err, 0, TRUE, DUPLICATE_SAME_ACCESS);//todo check ret

	siStartInfo.hStdOutput = out;
	siStartInfo.hStdError = err;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	CHAR* program = argv[1];
	CHAR programPath[MAX_PATH];
	std::cout << "looking for file" << std::endl;
	if (!findFile(program, programPath))
		error_exit("failed to find file");
	std::cout << "composing the command" << std::endl;
	CHAR cmd[BUF_SIZE];
	StringCchPrintfA(cmd, BUF_SIZE, "/c");
	for (int i = 2; i < argc; i++) {
		StringCchCatA(cmd, BUF_SIZE, " ");
		StringCchCatA(cmd, BUF_SIZE, argv[i]);
	}
	std::cout << cmd << std::endl;
	BOOL bSuccess = CreateProcessA(programPath, 
			cmd,	// command line
			NULL,		// process security attributes
			NULL,		// primary thread security attributes
			TRUE,		// handles are inherited
			0,			// creation flags
			NULL,		// use parent's environment
			NULL,		// use parent's current directory
			&siStartInfo,	// STARTUPINFO pointer
			&piProcInfo);	// receives PROCESS_INFORMATION
	
	/*BOOL bSuccess = CreateProcessA("./basic_process_test.exe", 
			"echo hello",	// command line
			NULL,		// process security attributes
			NULL,		// primary thread security attributes
			TRUE,		// handles are inherited
			0,			// creation flags
			NULL,		// use parent's environment
			NULL,		// use parent's current directory
			&siStartInfo,	// STARTUPINFO pointer
			&piProcInfo);	// receives PROCESS_INFORMATION
	*/
	if (!bSuccess)
		return -1;
	WaitForSingleObject( piProcInfo.hProcess, INFINITE );
	std::cout << "success" << std::endl;
	return 0;
}
