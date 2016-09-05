#include "Message.h"
#include "Folder.h"
#include <string>
#include <set>

void swap(Message &lhs, Message &rhs) {
	using std::swap;
	for (auto f : lhs.folders)
		f->remMeg(&lhs);
	for (auto f : rhs.folders)
		f->remMeg(&rhs);
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

void Message::save(Folder &f) {
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f) {
	folders.erase(&f);
	f.remMeg(this);
}

void Message::add_to_Folders(const Message& m) {
	for (auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message& m) :contents(m.contents), folders(m.folders) {
	add_to_Folders(m);
}

void Message::remove_from_Folders() {
	for (auto f : folders)
		f->remMeg(this);
}

Message::~Message() {
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs) {
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

void Message::addFolder(Folder* f) {
	folders.insert(f);
}

void Message::removeFolder(Folder* f) {
	folders.erase(f);
}