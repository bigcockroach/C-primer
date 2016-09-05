#ifndef FOLDER_H
#define FOLDER_H
#include <string>
#include <set>

class Folder {
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder&);
	Folder& operator=(const Folder&);
private:
	std::set<Message*> Messages;
	void addMsg(Message*);
	void remMeg(Message*);
	void add_to_Message(const Folder&);
	void remove_from_Message();
};

void swap(Folder&, Folder&);
#endif