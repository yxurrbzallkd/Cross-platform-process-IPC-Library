#include "coolexec.hpp"
#include <stdio.h>
#include <iostream>
#include "process.hpp"
#include "errors_and_warnings.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	std::vector<std::string> v(argv, argv + argc);
	pipc::process p(v);
	p.run_exec();
	pipc::process p("ls");
	p.run_exec(0, "file.txt", STDERR_FILENO);
	std::pair<string, string> r = p.run_grab(STDIN_FILENO);
	std::cout << r.first << " " << r.second << " " << p.get_result() << std::endl;
	if (argc == 1)
		error_exit("provide arguments");
	return 0;
}

	