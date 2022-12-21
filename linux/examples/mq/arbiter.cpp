 #include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_exit(const char* msg, int ern) {
	perror(msg);
	exit(ern);
}

int main() {
	unsigned int priority[1];
	priority[0] = 1;
	char name[] = "/mq_object";
	struct mq_attr attr;
    attr.mq_flags = O_NONBLOCK;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = O_NONBLOCK;
	mqd_t qd = mq_open(name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR, &attr);
	if (qd < 0) error_exit("failed to mq", -1);
	pid_t pid = fork();
	if (pid < 0) {
		error_exit("failed to fork", -3);
	} else if (pid == 0) {
		std::cout << "executing player" << std::endl;
		std::system("./player");
		exit(0);
	} else {
		for (int i = 0; i < 1000000; i++)
			continue;
		bool won = false;
		int v;
		int i = 0;
		while (1) {
			i++;
			v = rand() % 100 + 1;
			std::cout << "sending invitation" << std::endl;
			char invitation[32] = "send your guess, please: ";
			if (mq_send(qd, invitation, 32, priority[0]) < 0)
				error_exit("failed to send", -2);
			char rmsg[3];
			if (mq_receive(qd, rmsg, 3, priority) < 0)
				error_exit("failed to receive", -4);
			int guess = atoi(rmsg);
			std::cout << guess << " " << v << std::endl;
			if (guess == v) {
				won = true;
				break;
			}
		}
		if (won)
			std::cout << "guessed after " << i << " iterations" << std::endl;
	}
	return 0;
}
