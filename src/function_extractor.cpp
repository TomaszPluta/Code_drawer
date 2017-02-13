/*
 * method_extractor.cpp
 *
 *  Created on: 31 sty 2017
 *      Author: tomek
 */



#include "function_extractor.h"

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;



string extract_functions(string file_name)
{
	ifstream file_to_open(file_name.c_str());
	string content;
		if (file_to_open.is_open()) {
			content.append((istreambuf_iterator<char>(file_to_open)),(istreambuf_iterator<char>()));
		}
		size_t pos = content.find("){");
		size_t pos2 = content.rfind("(", pos, 1);
		size_t pos3 = content.rfind(" ", pos2, 1);
		size_t pos4 = content.rfind(" ", pos3-1, 1);


		string body_start = content.substr(pos);
		string method_name = content.substr(pos3);
		string returned_type = content.substr(pos4+1);



		cout <<pos; cout <<" : " + body_start<<endl;
		cout <<pos3; cout<< " : " + method_name <<endl;
		cout <<pos4; cout<<" : " + returned_type <<endl;


	return returned_type;
}



string extract_functions(string file_name, string function_to_parse)
{
	ifstream file_to_open(file_name.c_str());
	string content;
		if (file_to_open.is_open()) {
			content.append((istreambuf_iterator<char>(file_to_open)),(istreambuf_iterator<char>()));
		}

		size_t pos = content.find(function_to_parse);
		size_t pos1 = content.rfind(" ", pos-2, 1);


		string method_name = content.substr(pos);
		string returned_type = content.substr(pos1+1);



		cout <<pos; cout<< " : " + method_name <<endl;
		cout <<pos1; cout<<" : " + returned_type <<endl;


	return returned_type;
}


vector  <string> find_called(string file_name, string function_to_parse)
{
	ifstream file_to_open(file_name.c_str());
	string file_content;
	if (file_to_open.is_open()) {
		file_content.append((istreambuf_iterator<char>(file_to_open)),(istreambuf_iterator<char>()));
	}

	size_t pos = file_content.find(function_to_parse);
	size_t pos1 = file_content.find("){",pos, 1 );

	size_t pos2 = file_content.find("(",pos1, 1 ); //where function starts its argument
	size_t pos3 = file_content.rfind(" ", pos2, 1); //where function name starts
	size_t pos4 = file_content.find(")", pos2, 1 ); //where function ends its argument


	string function_arguments = file_content.substr(pos2);
	string function_name = file_content.substr(pos3+1);
	string function_all = file_content.substr(pos4);

	size_t len = pos4-pos3;
	function_name.resize((int)len);


	cout<< "founded calls: "<<endl;
	cout <<pos2; cout<< " : " + function_arguments <<endl;
	cout <<pos3; cout<<" : " + function_name <<endl;


	vector  <string> called_function;

	return called_function;
}
