#include "Folder.h"
#include "Message.h"
#include <set>
#include <string>

void swap(Folder& lhs, Folder& rhs) {
	using std::swap;
	for (auto m : lhs.Messages)
		m->removeFolder(&lhs);
	for (auto m : rhs.Messages)
		m->removeFolder(&rhs);
	swap(lhs.Messages, rhs.Messages);
	for (auto m : lhs.Messages)
		m->addFolder(&lhs);
	for (auto m : rhs.Messages)
		m->addFolder(&rhs);
}

void Folder::addMsg(Message* m) {
	Messages.insert(m);
}

void Folder::remMeg(Message* m) {
	Messages.erase(m);
}

void Folder::add_to_Message(const Folder& f) {
	for (auto m : f.Messages) {
		m->addFolder(this);
	}
}

void Folder::remove_from_Message() {
	for (auto m : Messages)
		m->removeFolder(this);
}

Folder::~Folder() {
	remove_from_Message();
}

Folder& Folder::operator=(const Folder& rhs) {
	remove_from_Message();
	Messages = rhs.Messages;
	add_to_Message(rhs);
	return *this;
}

Folder::Folder(const Folder& f) :Messages(f.Messages) {
	add_to_Message(f);
}