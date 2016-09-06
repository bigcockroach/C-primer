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
	chk_n_alloc();			//ȷ���пռ�������Ԫ��
	//��first_freeָ���Ԫ���й���s�ĸ���
	alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e) {
	//����ռ䱣�������Χ�е�Ԫ��
	auto data = alloc.allocate(e - b);
	//��ʼ��������һ��pair����data��uninitialized_copy�ķ���ֵ����
	return{ data, uninitialized_copy(b, e, data) };
}

//void test(std::string* s) {
//	StrVec::alloc.destroy(s);
//}

void test(std::string& s) {
	StrVec::alloc.destroy(&s);
}

void StrVec::free() {
	//���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0��do nothing
	if (elements) {
		//����ɾ��Ԫ��
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		//anthor type,for_each function must revice a reference
		//std::for_each(elements, first_free, test);
		//std::for_each(elements, first_free, [this](std::string& s){alloc.destroy(&s); });
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec& s) {
	//����alloc_n_copy����ռ���������s��һ�����Ԫ��
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
	auto dest = newdata;			// ָ������������һ������λ��
	auto elem = elements;			// ָ�����������һ��Ԫ��
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