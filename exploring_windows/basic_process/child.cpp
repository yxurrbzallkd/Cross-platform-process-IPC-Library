#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <iostream>

using namespace std;

int main(int argc, TCHAR *argv[]) 
{
	printf("->Start of child execution.\n");
	printf("hello world!\n");
	printf("->End of child execution.\n");
	return 0; 
}
