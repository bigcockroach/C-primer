#include "TextQuery.h"
#include<string>
#include<vector>
#include<map>
#include<set>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

TextQuery::TextQuery(ifstream &is) : file(new vector<string>) {
	string text;
	while (getline(is, text)) {
		file->push_back(text);				//stroe every line in file
		int n = file->size() - 1;			//line number
		istringstream line(text);			//stringstream will split a line into some single words by space 
		string word;
		while (line >> word) {
			//if the "word" not in wm, the wm will insert a set to store "word" and it's line_no
			auto &lines = wm[word];			// lines is a shared_ptr's reference
			if (!lines)						// the first time we meet the "word", lines will be nullptr
				lines.reset(new set<line_no>);		//create a new set
			lines->insert(n);				//insert the line number
		}
	}
}

QueryResult TextQuery::query(const string &sought) const {
	// if we can't find the word, we will return this shared_ptr
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}
