#include <iostream>
#include <string>
#include <initializer_list>

int function(std::initializer_list<std::string> strings) {
	int n = 0;
	for (auto s : strings) {
		std::cout << s;
		n++;
	}
	return n;
}

int main() {
	std::string a, b, c;
	a = "hello"; b = "Diana", c="!";
	std::cout << function({a, b, c}) << std::endl;
	return 0;
}

