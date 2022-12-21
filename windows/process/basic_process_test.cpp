#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>
#include <system_error>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 1)
		return -1;
	std::vector<std::string> v(argv+1, argv + argc);
	pipc::process p(v);
	std::cout << p.run_exec() << std::endl;
	std::cout << ::GetLastError() << std::endl;
	return 0;
}
