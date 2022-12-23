#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc == 1)
		return -1;
	char* name = argv[1];
	if (mkfifo(name, S_IWUSR | S_IRUSR) < 0) {
		perror("failed to mkfifo");
		return -1;
	}
	std::cout << mkfifo(name, S_IWUSR | S_IRUSR) << std::endl;
	pid_t pid = fork();
	if (pid < 0) {
		perror("failed to fork");
	}
	else if (pid == 0) {
		int rfd = open(name, O_RDONLY);
		if (rfd < 0) {
			perror("failed to open writing end");
		}
		char buf[16];
		int r = read(rfd, buf, 16);
		if (r < 0) {
			perror("failed to read");
		}
		buf[r] = '\0';
		if (close(rfd) < 0) {
			perror("failed to close reading end");
		}
		printf("%s\n", buf);
		exit(0);
	} else {
		int wfd = open(name, O_WRONLY);
		if (wfd < 0) {
			perror("failed to open writing end");
		}
		if (write(wfd, "hello world!", 12) < 0) {
			perror("failed to write");
		}
		if (close(wfd) < 0) {
			perror("failed to close writing end");
		}
	}
	if (unlink(name) < 0) {
		perror("failed to unlink");
		return -1;
	}
	printf("done\n");
	return 0;
}
