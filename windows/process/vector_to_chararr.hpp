#ifndef VECTOR_TO_CHAR_HEADER
#define VECTOR_TO_CHAR_HEADER

#include <vector>
#include <string>

char** vector_to_chararr(const std::vector<std::string>& args) {
	char** argv = (char**) malloc(sizeof(char*)*(args.size()+1));
    for (int i = 0; i < args.size(); i++)
        argv[i] = (char*)args[i].c_str();
    argv[args.size()] = NULL;
	return argv;
}

#endif