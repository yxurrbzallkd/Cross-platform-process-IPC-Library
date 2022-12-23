#include <stdio.h>
#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	pipc::process pa("echo hello world!");
	std::cout << pa.run_grab().first << std::endl;
	return 0;
}
