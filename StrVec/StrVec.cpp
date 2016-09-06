#include "StrVec.h"
#include <string>
#include <algorithm>

using namespace std;

StrVec::StrVec(initializer_list<string> il) {
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

void StrVec::push_back(const string& s) {
	chk_n_alloc();			//确保有空间容纳新元素
	//在first_free指向的元素中构造s的副本
	alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e) {
	//分配空间保存给定范围中的元素
	auto data = alloc.allocate(e - b);
	//初始化并返回一个pair，由data和uninitialized_copy的返回值构成
	return{ data, uninitialized_copy(b, e, data) };
}

//void test(std::string* s) {
//	StrVec::alloc.destroy(s);
//}

void test(std::string& s) {
	StrVec::alloc.destroy(&s);
}

void StrVec::free() {
	//不能传递给deallocate一个空指针，如果elements为0，do nothing
	if (elements) {
		//逆序删除元素
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		//anthor type,for_each function must revice a reference
		//std::for_each(elements, first_free, test);
		//std::for_each(elements, first_free, [this](std::string& s){alloc.destroy(&s); });
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec& s) {
	//调用alloc_n_copy分配空间以容纳与s中一样多的元素
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec& StrVec::operator=(const StrVec& s) {
	auto data = alloc_n_copy(s.begin(), s.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::alloc_n_move(size_t newcap) {
	auto newdata = alloc.allocate(newcap);
	auto dest = newdata;			// 指向新数组中下一个空闲位置
	auto elem = elements;			// 指向旧数组中下一个元素
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));
	free();							//free ram after move elements
	//update data
	elements = newdata;
	first_free = dest;
	cap = elements + newcap;
}

void StrVec::reallocate() {
	//new capacity of StrVec
	auto newcapacity = size() ? 2 * size() : 1;
	alloc_n_move(newcapacity);
}

void StrVec::reserve(size_t newcap) {
	if (newcap < capacity())
		return;
	alloc_n_move(newcap);
}

void StrVec::resize(size_t count) {
	resize(count, std::string());
}

void StrVec::resize(size_t count, const std::string& s) {
	if (count > size()) {
		if (count > capacity())
			reserve(count * 2);
		for (size_t i = size(); i != count; ++i)
			alloc.construct(first_free++, s);
	}
	else if (count < size()) {
		while (first_free != elements + count)
			alloc.destroy(--first_free);
	}
}