#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int open_dup(char* fpath, int flags, int ffd) {
	int fd = open(fpath, flags);
	if (fd < 0) return -1;
	if (dup2(fd, ffd) < 0) return -1;
	return fd;
}

int coolProcessRun(char* executable, char*  args[],
				char* in, char* out, char* err) {
	int fdIn = open_dup(in, R_OK, STDIN_FILENO);
	int fdOut = open_dup(out, W_OK, STDOUT_FILENO);
	int fdErr = open_dup(err, W_OK, STDERR_FILENO);
	if (fdIn < 0) return -1;
	if (fdOut < 0) return -1;
	if (fdErr < 0) return -1;
	int status = 0;
	if (fork() == 0)
		execvp(executable, args);
	else
		wait(&status);
	return status;
}

