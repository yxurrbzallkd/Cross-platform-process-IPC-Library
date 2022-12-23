#include "coolexec.hpp"
#include <stdio.h>
#include <iostream>
#include "coolprocess.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> args = {"../"};
	pipc::process p("ls", args);
	p.forward_stdout_to_file("file.txt");
	//p.run_system();
	int fd = open("file.txt", W_OK | O_CREAT);
	if (fd < 0) return -1;
	p.run_exec(-1, fd, fd);
	cout << p.get_result() << endl;
	return 0;
}
