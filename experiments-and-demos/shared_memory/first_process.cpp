#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <strsafe.h>

#define BUF_SIZE 256
TCHAR fname[] = TEXT("file.txt");
TCHAR szMsg[]=TEXT("Message from first process.");

HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

void ErrorExit(PTSTR lpszFunction) 

// Format a readable error message, display a message box, 
// and exit from the application.
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(1);
}


int _tmain()
{
	LPCTSTR pBuf;

	SECURITY_ATTRIBUTES saAttr; 

// Set the bInheritHandle flag so pipe handles are inherited. 
 
   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
   saAttr.bInheritHandle = TRUE; 
   saAttr.lpSecurityDescriptor = NULL; 

	if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) ) 
	      ErrorExit(TEXT("StdoutRd CreatePipe")); 

	// Ensure the read handle to the pipe for STDOUT is not inherited.

	if ( ! SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
	      ErrorExit(TEXT("Stdout SetHandleInformation")); 

	// Create a pipe for the child process's STDIN. 
	 
	if (! CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0)) 
	      ErrorExit(TEXT("Stdin CreatePipe")); 

	// Ensure the write handle to the pipe for STDIN is not inherited. 
	 
	if ( ! SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
	      ErrorExit(TEXT("Stdin SetHandleInformation")); 

	HANDLE hFile = CreateFile(fname,
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if ( hFile == INVALID_HANDLE_VALUE ) {
		printf("couldn't open file\n");
		return -1;
	}
	else {
		printf("opened file successfully\n");
	}

	HANDLE hMapFile = CreateFileMapping(
					  hFile,
					  NULL,			// default security
					  PAGE_READWRITE,// read/write access
					  0,	// 
					  BUF_SIZE,	// maximum object size (low-order DWORD)
					  fname);	// name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"),
				 GetLastError());
		return 1;
	} 
	else {
		printf("created a file mapping successfully\n");
	}
	pBuf = (LPTSTR) MapViewOfFile(hMapFile,	// handle to map object
								FILE_MAP_ALL_ACCESS, // read/write permission
								0,
								0,
								BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
				 GetLastError());

		 CloseHandle(hMapFile);

		return 1;
	}
	else {
		printf("created map view of file\n");
	}

	DWORD dwRead, dwWritten; 
	BOOL bErrorFlag = WriteFile( 
                hFile,           // open file handle
                pBuf,      // start of data to write
                dwRead,  // number of bytes to write
                &dwWritten, // number of bytes that were written
                NULL);            // no overlapped structure

	if (!bErrorFlag) {
		printf("couldn't write to file\n");
		return 1;
	}
	else {
		printf("wrote to file successfully\n");
	}

	PROCESS_INFORMATION piProcInfo; 
	STARTUPINFO siStartInfo;
 
// Set up members of the PROCESS_INFORMATION structure. 
 
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.hStdError = g_hChildStd_OUT_Wr;
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	printf("creating a process...\n");
	BOOL bSuccess = CreateProcess(NULL, 
		TEXT("second"),	  // command line 
		NULL,			 // process security attributes 
		NULL,			 // primary thread security attributes 
		TRUE,			 // handles are inherited 
		0,				 // creation flags 
		NULL,			 // use parent's environment 
		NULL,			 // use parent's current directory 
		&siStartInfo,  // STARTUPINFO pointer 
		&piProcInfo);  // receives PROCESS_INFORMATION 

	if (bSuccess) {
		printf("created process succesfully\n");
	}
	else {
		printf("failed to create process\n");
		return 1;
	}
	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}