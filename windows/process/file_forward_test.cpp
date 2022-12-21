#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>
#include <system_error>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 3)
		return -1;
	char* file = argv[1];
	std::string flag = std::string(argv[2]);
	pipc::process p("hello.exe");
	std::cout << "flag " << flag << std::endl;
	std::cout << p.set_forward_flag(flag) << std::endl;
	std::cout << p.forward_stdout(file) << std::endl;
	std::cout << "result " << p.run_exec() << std::endl;
	std::cout << "last error " << ::GetLastError() << std::endl;
	return 0;
}
