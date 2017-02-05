/*
 * method_extractor.cpp
 *
 *  Created on: 31 sty 2017
 *      Author: tomek
 */



#include <iostream>
#include <fstream>
#include <string.h>
#include "method_extractor.h"
using namespace std;



string extract_method(string file_name)
{
	ifstream file_to_open;
	string content;
	string line;
	file_to_open.open(file_name.c_str());
		if (file_to_open.is_open()) {

			while ( getline (file_to_open,line) )
		    {
				cout << line << '\n';
			}
			file_to_open.close();
		}

	return line;
}
