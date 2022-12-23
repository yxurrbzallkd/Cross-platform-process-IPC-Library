#include <stdio.h>
#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	char * folder = ".";
	if (argc > 1)
		folder = argv[1];
	// executing ls <folder> | grep .txt | ./rw | wc
	pipc::process p1("ls", {folder});
	pipc::process p2("grep", {".txt"});
	pipc::process p3("./rw");
	pipc::process p4("wc");
	pipc::pipe_execute({p1, p2, p3, p4});
	return 0;
}
