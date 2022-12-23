#include <stdio.h>
#include <iostream>
#include "process.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

	std::string s = "";
	for (int i = 1; i < argc; i++)
		s += std::string(argv[i])+" ";

	std::vector<pipc::process> p;
	size_t pos = s.find("-");
	while (pos != std::string::npos) {
		p.push_back(pipc::process(s.substr(0, pos)));
		s = s.substr(pos+1, s.size()-pos-1);
		pos = s.find("\\");
	}
	p.push_back(pipc::process(s));
	pipc::pipe_execute(p);
	return 0;
}
