#ifndef STRVEC_H
#define STRVEC_H
#include <string>

//类vector类内存分配策略的简化实现
class StrVec{
	//friend void test(std::string*);
	friend void test(std::string&);
public:
	StrVec() :	//allocator成员进行默认初始化
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(initializer_list<string>);
	StrVec(const StrVec&);					//拷贝构造函数
	StrVec& operator=(const StrVec&);		//拷贝赋值运算符
	~StrVec();								//析构函数
	void push_back(const std::string&);		//拷贝元素
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const std::string&);
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
private:
	static std::allocator<std::string> alloc; //分配元素
	void chk_n_alloc() {
		if (size() == capacity()) reallocate();
	}
	//工具函数拷贝n个数据，被拷贝构造函数、赋值运算符和析构函数所使用
	std::pair<std::string*, std::string*> alloc_n_copy
		(const std::string*, const std::string*);
	void alloc_n_move(size_t);		//移动n个数据
	void free();							//销毁元素并释放内存
	void reallocate();						//获得更多内存并拷贝已有元素
	std::string* elements;					//指向数组首元素的指针
	std::string* first_free;				//指向数组第一个空闲元素的指针
	std::string* cap;						//指向数组尾后位置的指针
};

#endif