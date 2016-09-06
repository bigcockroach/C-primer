#ifndef STRVEC_H
#define STRVEC_H
#include <string>

//��vector���ڴ������Եļ�ʵ��
class StrVec{
	//friend void test(std::string*);
	friend void test(std::string&);
public:
	StrVec() :	//allocator��Ա����Ĭ�ϳ�ʼ��
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(initializer_list<string>);
	StrVec(const StrVec&);					//�������캯��
	StrVec& operator=(const StrVec&);		//������ֵ�����
	~StrVec();								//��������
	void push_back(const std::string&);		//����Ԫ��
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const std::string&);
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
private:
	static std::allocator<std::string> alloc; //����Ԫ��
	void chk_n_alloc() {
		if (size() == capacity()) reallocate();
	}
	//���ߺ�������n�����ݣ����������캯������ֵ�����������������ʹ��
	std::pair<std::string*, std::string*> alloc_n_copy
		(const std::string*, const std::string*);
	void alloc_n_move(size_t);		//�ƶ�n������
	void free();							//����Ԫ�ز��ͷ��ڴ�
	void reallocate();						//��ø����ڴ沢��������Ԫ��
	std::string* elements;					//ָ��������Ԫ�ص�ָ��
	std::string* first_free;				//ָ�������һ������Ԫ�ص�ָ��
	std::string* cap;						//ָ������β��λ�õ�ָ��
};

#endif