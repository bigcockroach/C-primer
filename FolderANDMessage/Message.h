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
	//folders被隐式初始化为空集合
	explicit Message(const std::string &str = "") : contents(str) {}
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	//从给定Folder集合中添加/删除本Message
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents;				// 实际消息文本
	std::set<Folder*> folders;			// 包含本message的folder
	// 将本Message添加到指向参数的Folder中
	void add_to_Folders(const Message&);
	//从folders中的每个Folder中删除本Message
	void remove_from_Folders();
	void addFolder(Folder*);
	void removeFolder(Folder*);
};

void swap(Message&, Message&);
#endif