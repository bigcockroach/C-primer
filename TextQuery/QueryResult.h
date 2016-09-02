#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<set>

class QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	using line_no = std::vector<std::string>::size_type;
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) :
		sought(s), lines(p), file(f) {}
private:
	std::string sought;		// the word will be query
	std::shared_ptr<std::set<line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};

std::string make_plural(size_t ctr, const std::string& word, const std::string& end) {
	return ctr == 1 ? word : word + end;
}

std::ostream& print(std::ostream& os, const QueryResult &qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
	for (auto num : *(qr.lines))
		//os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
		os << "\t(line " << num + 1 << ") " << qr.file->at(num) << std::endl;
	return os;
}



#endif