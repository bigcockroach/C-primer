#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <set>
#include "Folder.h"

class Message{
	friend class Folder;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);
public:
	//folders����ʽ��ʼ��Ϊ�ռ���
	explicit Message(const std::string &str = "") : contents(str) {}
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	//�Ӹ���Folder���������/ɾ����Message
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents;				// ʵ����Ϣ�ı�
	std::set<Folder*> folders;			// ������message��folder
	// ����Message��ӵ�ָ�������Folder��
	void add_to_Folders(const Message&);
	//��folders�е�ÿ��Folder��ɾ����Message
	void remove_from_Folders();
	void addFolder(Folder*);
	void removeFolder(Folder*);
};

void swap(Message&, Message&);
#endif