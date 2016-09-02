#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include "QueryResult.h"
#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<memory>

class QueryResult;
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> file;			//inpute file
	std::map < std::string, std::shared_ptr<std::set<line_no>>> wm; //a map store every words to their line number
};


#endif

