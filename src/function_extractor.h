/*
 * method_extractor.h
 *
 *  Created on: 31 sty 2017
 *      Author: tomek
 */

#ifndef FUNCTION_EXTRACTOR_H_
#define FUNCTION_EXTRACTOR_H_

#include <string>
#include <vector>
using namespace std;



string extract_functions(string file_name);
string extract_functions(string file_name, string function_to_parse);
vector  <string> find_called(string file_name, string function_to_parse);
vector  <string> find_called(string function_to_parse);


class ExtractedFunction{
	string name;
	string body;
	string args;
	string retval;
	vector <ExtractedFunction *> called_functions;
public:
	ExtractedFunction(string name_, string fbody_, string args_, string retval_);
	string get_function_name();
	vector <ExtractedFunction *> get_called();
};

class FileToDraw{
	string file_content;
	vector <ExtractedFunction*> functions;
public:
	void open(string file_name);
	void parse(void);
};



#endif /* FUNCTION_EXTRACTOR_H_ */
