#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <iostream>

using namespace std;

#define BUFSIZE 4

HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

HANDLE g_hInputFile = NULL;

void CreateChildProcess(void);
void ErrorExit(const string);

int _tmain(int argc, TCHAR *argv[]) 
{
	printf("->Start of parent execution.\n");
	SECURITY_ATTRIBUTES saAttr;
	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT. 
	if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) )
		ErrorExit("StdoutRd CreatePipe");
	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if ( ! SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
		ErrorExit("Stdout SetHandleInformation"); 
	// Create a pipe for the child process's STDIN. 
	if (! CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0) )
		ErrorExit("Stdin CreatePipe");
	// Ensure the write handle to the pipe for STDIN is not inherited. 
	if ( ! SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
		ErrorExit("Stdin SetHandleInformation");

	// Create a child process that uses the previously created pipes for STDIN and STDOUT.
	TCHAR szCmdline[]=TEXT("child");
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;

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

	// Create the child process. 
	bSuccess = CreateProcess(NULL, 
			szCmdline,	// command line
			NULL,		// process security attributes
			NULL,		// primary thread security attributes
			TRUE,		// handles are inherited
			0,			// creation flags
			NULL,		// use parent's environment
			NULL,		// use parent's current directory
			&siStartInfo,	// STARTUPINFO pointer
			&piProcInfo);	// receives PROCESS_INFORMATION

	// If an error occurs, exit the application.
	if ( ! bSuccess ) 
		ErrorExit("CreateProcess");
	else {
		// Close handles to the child process and its primary thread.
		// Some applications might keep these handles to monitor the status
		// of the child process, for example.
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		// Close handles to the stdin and stdout pipes no longer needed by the child process.
		// If they are not explicitly closed, there is no way to recognize that the child process has ended.
		CloseHandle(g_hChildStd_OUT_Wr);
		CloseHandle(g_hChildStd_IN_Rd);
	}

	// Get a handle to an input file for the parent. 
	// This example assumes a plain text file and uses string output to verify data flow. 
	if (argc == 1)
		ErrorExit("Please specify an input file"); 

	g_hInputFile = CreateFile(
		argv[1], 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_READONLY, 
		NULL); 

	if ( g_hInputFile == INVALID_HANDLE_VALUE ) 
		ErrorExit("CreateFile"); 

	// Write to the pipe that is the standard input for a child process.
	// Data is written to the pipe's buffers, so it is not necessary to wait
	// until the child process is running before writing data.
	DWORD dwRead, dwWritten;
	CHAR chBuf[BUFSIZE];
 
	for (;;) 
	{
		bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL);
		if ( ! bSuccess || dwRead == 0 ) break;
		bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL);
		if ( ! bSuccess ) break;
	}
	// Close the pipe handle so the child process stops reading.
	if ( ! CloseHandle(g_hChildStd_IN_Wr) ) 
		ErrorExit("StdInWr CloseHandle"); 
	printf("->Contents of %S written to child STDIN pipe.\n", argv[1]);

	// Read from pipe that is the standard output for child process. 
	printf("->Contents of child process STDOUT:\n\n");
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (;;) 
	{
		bSuccess = ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		if( ! bSuccess || dwRead == 0 ) break;
		bSuccess = WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, NULL);
		if (! bSuccess ) break;
	}
	printf("->End of parent execution.\n");
	// The remaining open handles are cleaned up when this process terminates.
	// To avoid resource leaks in a larger application, close handles explicitly. 
	return 0; 
}
 
void ErrorExit(const string message) {
	cerr << message << " failed with error " << GetLastError() << endl;
	ExitProcess(1);
}
