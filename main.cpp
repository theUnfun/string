#include <iostream>
#include <vector>
#include <algorithm>
#include "mystring.h"

using my_string::String;

std::ostream& operator<<(std::ostream& out, const String& str){
	out << str.c_str();
	return out;
}

std::istream& operator>>(std::istream& in, String& str) {
	char buffer[1024];
	in >> buffer;
	str = buffer;
	return in;
}

String operator "" _s(const char* str, size_t size) {
	return String(str, size);
}

bool CaseInsensitiveComparator(const String& a, const String& b) {
	const auto* left = a.c_str();
	const auto* rigth = b.c_str();
	for (size_t i = 0; i < std::min(a.length(), b.length()); ++i) {
		if (std::toupper(*(left + i)) < std::toupper(*(rigth + i)))
			return true;
		if (std::toupper(*(left + i)) > std::toupper(*(rigth + i)))
			return false;
	}
	return a.length() < b.length();
}

int main() {
	std::vector<String> v;
	std::cout << "Enter a number of strings:" << std::endl;

	int i = 0;
	std::cin >> i;

	while (i > 0) {
		String temp;
		std::cin >> temp;
		v.emplace_back(std::move(temp));
		--i;
	}

	std::sort(v.begin(), v.end(), [](const String& left, const String& right) {return !CaseInsensitiveComparator(left, right); });

	std::for_each(v.begin(), v.end(), [](const String& str) { std::cout << str << " "; });


	/*String s1 = "g" + "gf"_s;
	String s2 = "gwg"_s + "gfwg";
	String s3 = std::move(s2);*/
}

