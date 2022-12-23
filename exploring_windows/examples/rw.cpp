#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include <string>

using namespace std;

#define BUF_SIZE 1024

int main() {
	char buf[BUF_SIZE];
	int r = BUF_SIZE;
	while (r == BUF_SIZE) {
		r = read(STDIN_FILENO, buf, BUF_SIZE);
		if (r < 0)
			return -1;
		write(STDOUT_FILENO, buf, r);
	}
	return 0;
}

