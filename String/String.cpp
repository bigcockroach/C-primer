#include "String.h"
#include <memory>
#include <algorithm>

std::pair<char*, char*>
String::alloc_n_copy(const char* b, const char* e) {
	auto data = alloc.allocate(e - b);
	return{ data, std::uninitialized_copy(b, e, data) };
}

void String::range_initializer(const char* first, const char* last) {
	auto newStr = alloc_n_copy(first, last);
	elements = newStr.first;
	end = newStr.second;
}

String::String(const char* c) {
	char* newc = const_cast<char*>(c);
	while (*newc)
		++newc;
	range_initializer(c, newc);
}

String::String(const String& s) {
	range_initializer(s.elements, s.end);
}

void String::free() {
	if (elements) {
		std::for_each(elements, end, [this](char& c){alloc.destroy(&c); });
		alloc.deallocate(elements, end - elements);
	}
}

String::~String() {
	free();
}

String& String::operator=(const String& s) {
	auto newS = alloc_n_copy(s.elements, s.end);
	free();
	elements = newS.first;
	end = newS.second;
	return *this;
}