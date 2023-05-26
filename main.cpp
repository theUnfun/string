#include <iostream>
#include <vector>
#include <algorithm>
#include "mystring.h"

using my_string::String;

std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.c_str();
	return out;
}

std::istream& operator>>(std::istream& in, String& str) {
	char buffer[1024];
	in.getline(buffer, 1024);
	str = buffer;
	return in;
}

String operator "" _s(const char* str, size_t size) {
	return String(str);
}

int main() {
	std::vector<String> v;
	std::cout << "Enter a number of strings:"_s << std::endl;

	int i = 0;
	std::cin >> i;
	std::cin.ignore();

	while (i > 0) {
		String temp;
		std::cin >> temp;
		v.emplace_back(std::move(temp));
		--i;
	}

	std::sort(v.begin(), v.end(), [](const String& left, const String& right) {return right < left; });

	std::for_each(v.begin(), v.end(), [](const String& str) { std::cout << str << " "; });

}

