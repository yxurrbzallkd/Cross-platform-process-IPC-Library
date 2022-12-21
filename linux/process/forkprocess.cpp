#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	pipc::process p1("ls -l");
	pipc::process p2("grep -E .cpp");
	pipc::process p3("wc");
	
	std::vector<pipc::process> p = {p1, p2, p3};
	int pipes[2][2];
	for (int i = 0; i < 2; i++)
		if (pipe(pipes[i]) < 0)
			return -1;

	pid_t pid;
	for (int i = 0; i < p.size(); i++) {
		if (i != 0)
			p[i].forward_stdin(pipes[i-1][0]);
		if (i != p.size()-1)
			p[i].forward_stdout(pipes[i][1]);
	}
	for (int i = 0; i < p.size(); i++) {
		std::cout << "starting " << i << std::endl;
		if (i != 0)
			close(pipes[i-1][0]);
		pid = fork();
		if (pid < 0)
			return -1;
		if (pid == 0) {
			if (i != 0)
				close(pipes[i-1][1]);
			if (i != p.size()-1)
				close(pipes[i][0]);
			p[i].run_exec();
			std::cout << "executed " << i << std::endl;
			for (int j = 0; j < p.size()-1; j++) {
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			exit(p[i].get_result());
		}
		if (i != 0)
			close(pipes[i-1][1]);
	}
	std::cout << "closing all pipes" << std::endl;
	for (int i = 0; i < p.size()-1; i++) {
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	for (int i = 0; i < p.size(); i++) {
		std::cout << "watiting " << i << std::endl;
		wait(NULL);
	}
	/*
	int pipe12[2];
	int pipe23[2];
	if ((pipe(pipe12) < 0) || (pipe(pipe23) < 0))
		return -1;
	pid_t pid12 = fork();
	if (pid12 < 0)
		return -1;
	if (pid12 == 0) {
		p1.forward_stdout(pipe12[1]);
		close(pipe12[0]);
		p1.run_exec();
		exit(p1.get_result());
	} else {
		pid_t pid23 = fork();
		if (pid23 < 0)
			return -1;
		if (pid23 == 0) {
			p2.forward_stdin(pipe12[0]);
			p2.forward_stdout(pipe23[1]);
			close(pipe12[1]);
			close(pipe23[1]);
			p2.run_exec();
			exit(p2.get_result());
		} else {
			p3.forward_stdin(pipe23[0]);
			p3.run_exec();
		}
		
	}
	*/
	return 0;
}
