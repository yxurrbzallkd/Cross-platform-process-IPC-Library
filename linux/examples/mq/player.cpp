 #include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
int main() {
	unsigned int priority[1];
	priority[0] = 1;
	char name[] = "/mq_object";
	mqd_t qd = mq_open(name, O_RDWR);
	if (qd < 0) exit(-1);
	char guess[3];
	char msg[32];
	size_t end;
	while (1) {
		sprintf(guess, "%d", rand() % 100 + 1);
		std::cout << "receiving" << std::endl;
		end = mq_receive(qd, msg, 32, priority);
		if (end < 0) exit(-1);
		std::cout << "message: " << msg << std::endl;
		if (std::string(msg) == "send your guess, please")
			if (mq_send(qd, guess, 3, 2) < 0)
				exit(-1);
			else
				exit(0);
		else exit(-1);
	}
	return 0;
}
