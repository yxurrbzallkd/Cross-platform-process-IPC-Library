#include <stdio.h>
#include <iostream>
#include "fifo.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	char * fifo_name = "/tmp/fifo";
	if (argc > 1)
		fifo_name = argv[1];
	pid_t pid = fork();
	if (pid < 0)
		return -1;
	if (pid == 0) {
		sleep(1);
		pipc::fifo fc(fifo_name, false, O_RDONLY);
		sleep(1);
		fc.setup();
		char buf[1024];
		int res = fc.read_fifo(buf, 1024);
		std::cout << buf << std::endl;
		std::cout << res << std::endl;
		exit(res);
	} else {
		pipc::fifo fp(fifo_name, true, O_WRONLY);
		fp.setup();
		char hello[13] = "hello world!";
		fp.write_fifo(hello, 13);
		sleep(1);
		int status;
		waitpid(pid, &status, 0);
		fp.unlink_fifo();
		return 0;
	}
	return 0;
}
