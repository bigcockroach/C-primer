#ifndef HASPTR_H
#define HASPTR_H
#include <string>

class HasPtr{
public:
	HasPtr(const std::string&s = std::string()) :
		ps(new std::string(s)), i(0) {}
	HasPtr(const HasPtr &p) :ps(new std::string(*p.ps)), i(p.i) {}
	HasPtr& operator=(const HasPtr &);
	~HasPtr() { delete ps; }
private:
	std::string *ps;
	int i;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
	auto newp = new std::string(*rhs.ps);			//拷贝底层string
	delete ps;				//这一行千万不能跟上一行的顺序弄反，如果rhs和this是同一个对象，就会先释放内存中的数据而无法正常拷贝
	ps = newp;
	i = rhs.i;
	return *this;			//返回本对象
}

#endif