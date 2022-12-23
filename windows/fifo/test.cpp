#include "fifo.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	CHAR name[] = "\\\\.\\pipe\\Pipe";
	CHAR programPath[] = "./test.exe";
	if (argc == 2) {
		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;
		ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
		ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
		siStartInfo.cb = sizeof(STARTUPINFO);

		pipc::fifo pipe(name);
		if (pipe.setup() != SUCCESS)
			return -1;

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
		if (!bSuccess)
			return -1;
		CHAR buf[1024];
		DWORD dwRead;
		pipe.read_fifo(buf, 1024, dwRead);
		buf[dwRead] = '\0';
		std::cout << buf << std::endl;
	} else {
		// child
		CHAR* hello = (char*)"hello world!";
		DWORD dwWritten;
		pipc::fifo pipe(name, GENERIC_WRITE);
		if (pipe.setup() != SUCCESS)
			return -1;
		pipe.write_fifo(hello, 13, dwWritten);
	}
	return 0;
}

