#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	std::vector<std::string> v(argv+1, argv + argc);
	pipc::process p(v);
	p.run_exec();
	return 0;
}
