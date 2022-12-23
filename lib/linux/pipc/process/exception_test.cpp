#include "errors_and_warnings.hpp"
#include <string>
#include <cassert>
#include <cstring>

int main() {
	std::string msg = "testing custom exception";
	try {
		throw PipeError(msg);
		return -1;
	} catch (CustomException e) {
		assert(!strcmp(("PipeError: "+msg).c_str(), e.what()));
	}
	exit(0);
}
