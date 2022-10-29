#include <unistd.h>
#include <iostream>
#include <fcntl.h>

#define BUFSIZE 4096

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2)
		return 1;
	char buf[BUFSIZE];
	for (int i = 1; i < argc; i++) {
		if (access(argv[i], R_OK)<0) {
			cout << "invalid file" << argv[1] << endl;
			return 2;
		}
		int pipefd[2];
		if (pipe(pipefd)!=0) {
			cout << "pipe failed" << endl;
			return 1;
		}
		if (fork()==0) {
			cout << "parent process receiving" << argv[i] << endl;
			close(pipefd[1]);
			while (true) {
				if (read(pipefd[0], buf, BUFSIZE) == 0)
					break;
				cout << buf << endl;
			}
		} else {
			cout << "child process sending" << argv[i] << endl;
			int fd = open(argv[i], R_OK);
			if (fd<0) {
				cout << "failed to open " << argv[1] << endl;
		    }
			close(pipefd[0]);
			int n;
			while (true) {
				n = read(fd, buf, BUFSIZE);
				if (n==0)
					break;
				write(pipefd[1], buf, n);
			}
		}
	}
	return 0;
}
