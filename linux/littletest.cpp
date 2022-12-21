#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>


int main(int argc, char* argv[]) {
	char* program = "ls";
	char* args[4];
	args[0] = program;
	args[1] = ">";
	args[2] = "file.txt";
	args[3] = NULL;
	execvp(program, args);
}