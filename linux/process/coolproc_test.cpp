#include "coolexec.hpp"
#include <stdio.h>
#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	std::cout << "executing ls | grep | ./rw | wc" << std::endl;
	pipc::process p1("ls", {"../"});
	pipc::process p2("grep", {".cpp"});
	pipc::process p3("./rw");
	pipc::process p4("wc");
	pipc::pipe_execute({p1, p2, p3, p4});
	return 0;
}
