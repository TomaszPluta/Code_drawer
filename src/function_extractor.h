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


#endif /* FUNCTION_EXTRACTOR_H_ */
