#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <iostream>

using namespace std;

#define BUFSIZE 4096 

int main(int argc, TCHAR *argv[]) 
{ 
	printf("->Start of parent execution.\n");
	// Set the bInheritHandle flag so pipe handles are inherited.
	TCHAR szCmdline[]=TEXT("child");
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;

	ZeroMemory( &siStartInfo, sizeof(siStartInfo) );
    siStartInfo.cb = sizeof(siStartInfo);
    ZeroMemory( &piProcInfo, sizeof(piProcInfo) );

	// Create the child process. 
	BOOL bSuccess = CreateProcess(NULL, 
		szCmdline,		// command line 
		NULL,			// process security attributes 
		NULL,			// primary thread security attributes 
		TRUE,			// handles are inherited 
		0,				// creation flags 
		NULL,			// use parent's environment 
		NULL,			// use parent's current directory 
		&siStartInfo,	// STARTUPINFO pointer 
		&piProcInfo);	// receives PROCESS_INFORMATION 

	// If an error occurs, exit the application. 
	if ( ! bSuccess ) {
		printf("Failed to create child process\n");
		return -1;
	}
    WaitForSingleObject( piProcInfo.hProcess, INFINITE ); // Wait until child process exits.
    /* Close handles to the child process and its primary thread.
	 Some applications might keep these handles to monitor the status
	 of the child process, for example. */
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);
	printf("->End of parent execution.\n");
	// The remaining open handles are cleaned up when this process terminates. 
	// To avoid resource leaks in a larger application, close handles explicitly. 
	return 0; 
} 
