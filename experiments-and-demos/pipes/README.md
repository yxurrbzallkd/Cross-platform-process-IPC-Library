# Purpose

the point of this document is to illustrates the differences of windows and linux

# The Program

- pass a file to the program
- create a child process
- connect them with a pipe
- child process will be reading the file and sending it to the parent who will print it out

# Differences

### ```fork()```

Windows does not have a ```fork()``` syscall. To create a process you nedd to use ```CreateProcess``` from ```<windows.h>```.

```c++
CreateProcess( NULL,   // No module name (use command line)
        argv[1],        // Command line (name of the program)
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
```

Pay attention to ```STARTUPINFO``` and ```PROCESS_INFORMATION``` at the end.

- ```PROCESS_INFORMATON```

from ```processthreadsapi.h```

```c++
typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess; // a handle to the newly created process, is used to specify the process in all functions that perform operations on the process object
  HANDLE hThread; // a handle to the primary thread of the newly created process
  DWORD  dwProcessId; // process id, used to identify a process
  DWORD  dwThreadId; // a value used to identify a thread
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;
/* 
if the function succeeds, call CloseHandle to close hProcess and hThread handles,
otherwise when child process exits, the system cannot clean up the process structures for the child process, 
because the parent process still has open handles to the child process
*/
```

```c++
typedef struct _STARTUPINFOA {
  DWORD  cb; // size of the structure in bytes
  LPSTR  lpReserved; // must be NULL
  LPSTR  lpDesktop; // the name of the desktop and window station for this process
  LPSTR  lpTitle; // title displayed in the title bar if a new console window is created. if NULL - name of the executable is used
  DWORD  dwX; // used to specify startup location of the program window
  DWORD  dwY; // same as dwX
  DWORD  dwXSize; // used to specify startup size of the window
  DWORD  dwYSize; // same as dwYSize
  DWORD  dwXCountChars; // if a new console window is created in a console process, this member specifies the screen buffer width, in character columns
  DWORD  dwYCountChars; // same as dwXCountChars
  DWORD  dwFillAttribute; // can be used to specify the initial text and background colors if a new console window is created in a console application
  DWORD  dwFlags; // A bitfield that determines whether certain STARTUPINFO members are used when the process creates a window
  WORD   wShowWindow; // ?????????
  WORD   cbReserved2; // Reserved for use by the C Run-time; must be zero.
  LPBYTE lpReserved2; // Reserved for use by the C Run-time; must be zero.

  HANDLE hStdInput; // we can specify stdin handle for the process!!!
  HANDLE hStdOutput; // we can specify stdout handle for the process!!!
  HANDLE hStdError; // we can specify stderror handle for the process!!!
} STARTUPINFOA, *LPSTARTUPINFOA;
```

[more on ```HANDLE```s in Windows and their difference to Unix file descriptors](http://lackingrhoticity.blogspot.com/2015/05/passing-fds-handles-between-processes.html)

[and here](https://stackoverflow.com/questions/902967/what-is-a-windows-handle)

Short summary:
- fd is an index in fd table - ```int```s
- HANDLE is ```typedef```ed to to ```void *```, but really a 32 bit index
- HANDLE is NOT a pointer into the process's address space
- fd object is what fd number maps to. User code never seees fd objects diretly
- multiple fd objects cam map to the same FD objects
- The above also applies to HANDLEs

- On Windows, we have ```DuplicateHandle()``` - it allows to modify another process's handle table.
- On Unix, process fd table is private to the process

#### Sending a handle\FD to another process
- To send a HANDLE to another process on Windows
	1. call ```DuplicateHandle()``` (need the destinations process handle) - returns a handle number indexing into the destination's handle table
	2. sender must send the handle number to the destination - using ```WriteFile()``` - sends a message via a pipe

- On Unix: 
	1. sender - ```sendmsg()``` syscall - gives fd *number* to the ```cmsg\CSM_RIGHTS``` interface, the ***kernel*** translates this into an fd *object* and copies the reference to that object to socket's message buffer
	2. receiver - ```recvmsg()``` - removes fd object from the socket's message buffer and adds to the fd table, allocating a new number in that table

notice, we are not talking about a network socket, but about an IPC socket \ aka Unix Domain socket

### Implications

I only remembered 2, and copied the third one, because it is important, but feel free to read all of them in the article
- 
- Windows has process handles. Unix does not have an equivalent concept, although FreeBSD has process FDs
- Namespace Hazards - ```DuplicateHandle()``` gives you an index into ANOTHER PROCESS's handle table, so DON'T CALL ```CloseHandle()``` on it etc.
- ? Unix emultaion: that difference between how Windows and Unix send HANDLEs\FDs between processes makes it hard to emulate Unix domain sockets on Windows  

For even more, see this post: https://stackoverflow.com/questions/62731834/is-there-a-unix-domain-socket-analog-on-windows
It is very interesting

# Code Differences

```c++
// Linux
int pipefd[2];
pipe(pipefd);
if (fork() == 0)
  close(pipefd[0])
  child_stuff()
else
  close(pipefd[1])
  parent_stuff()
```

```C++
//Windows
void CreateChildProcess()
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{ 
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
   cout << "CreateProcess" << endl;
   bSuccess = CreateProcess(NULL, 
      szCmdline,     // command line 
      NULL,          // process security attributes 
      NULL,          // primary thread security attributes 
      TRUE,          // handles are inherited 
      0,             // creation flags 
      NULL,          // use parent's environment 
      NULL,          // use parent's current directory 
      &siStartInfo,  // STARTUPINFO pointer 
      &piProcInfo);  // receives PROCESS_INFORMATION 
   
   // If an error occurs, exit the application. 
   if ( ! bSuccess ) 
      ErrorExit(TEXT("CreateProcess"));
   else 
   {
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
}
```
