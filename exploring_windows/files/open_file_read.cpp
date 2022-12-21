#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <iostream>
#include <string>

using namespace std;

#define BUFSIZE 5

int main(int argc,  TCHAR *argv[]) {
	HANDLE g_hInputFile = CreateFile(
						argv[1],
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_READONLY,
						NULL);

	if ( g_hInputFile == INVALID_HANDLE_VALUE ) {
		printf("invalid file\n");
		return -1;
	}

	DWORD dwRead, dwWritten;
	CHAR chBuf[BUFSIZE+1];
	BOOL bSuccess = FALSE;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (;;)
	{
		bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL);
		if ( ! bSuccess || dwRead == 0 ) break;
		//cout << std::string(chBuf);
		/*for (int i = 0; i < dwRead; i++) {
			cout << chBuf[i];
		}*/
		/*string s(chBuf);
		cout << s;*/
		bSuccess = WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL);
		if (! bSuccess || dwWritten == 0) break;
	}
	cout << endl;
	CloseHandle(g_hInputFile);
}
