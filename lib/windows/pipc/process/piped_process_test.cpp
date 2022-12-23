#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>
#include <system_error>

using namespace std;

int main(int argc, char* argv[]) {
	pipc::process p1("cmd.exe /c echo bin");
	pipc::process p2("cmd.exe /c dir");
	std::cout << pipc::pipe_execute({p1, p2}) << std::endl;
	std::cout << ::GetLastError() << std::endl;
	return 0;
}
