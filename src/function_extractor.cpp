/*
 * method_extractor.cpp
 *
 *  Created on: 31 sty 2017
 *      Author: tomek
 */



#include "function_extractor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
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



ExtractedFunction::ExtractedFunction(string name_, string body_, string args_, string retval_)
{
	name = name_;
	body = body_;
	args = args_;
	retval = retval_;
}


void FileToDraw::open(string file_name){
	ifstream file_to_open(file_name.c_str());

	if (file_to_open.is_open()){
		file_content.append(istreambuf_iterator<char>(file_to_open), istreambuf_iterator<char>());
	}
}


static void prv_remove_comments_from_function (string& body)
{
	size_t pos_comment_mark = 0;
	while((pos_comment_mark !=  string::npos) )
	{
		pos_comment_mark= body.find("//", pos_comment_mark, 2);
		if (pos_comment_mark !=  string::npos)
		{
			size_t pos_end_line;
			pos_end_line = body.find("\n", pos_comment_mark, 1);
			if (pos_end_line  !=  string::npos)
			{
				int len = pos_end_line - pos_comment_mark;
				body.erase(pos_comment_mark, len);
			}
			pos_comment_mark++;
		}
	}
}




static bool prv_is_controll_expression (const string& express)
{
	if ((express.compare(0, 2, "if")    ==0) ||
		(express.compare(0, 2, "for")   ==0) ||
	    (express.compare(0, 5, "while") ==0)) {
			return true;
	}
	return false;
}




void FileToDraw::parse(){
	size_t pos = 0;
	uint32_t i=0;
	int j =0;
	int cnt =0;
	size_t fsize = file_content.size();
	while (pos <= fsize)
	{
		 pos = file_content.find(")", pos, 1);
		 if (pos == string::npos){
			 break;
		 }
		 while (pos < file_content.length() )
		 {

		    if (file_content.at(pos) == '{'){

		    	size_t pos_args = file_content.rfind("(", pos, 1);
				size_t pos_name = file_content.rfind(" ", pos_args, 1);
				size_t pos_ret_val = file_content.rfind(" ", pos_name-1, 1);
				size_t pos_end_function = file_content.find("}", pos, 1);


				string retval = file_content.substr(pos_ret_val+1, (pos_name-pos_ret_val+1));
				string name  = file_content.substr(pos_name, (pos_args-pos_name));
				string body  = file_content.substr(pos+1, pos_end_function);
				string args  = file_content.substr(pos_args, pos);

				if (prv_is_controll_expression(retval))	{
					pos++;
					continue;
				}

				prv_remove_comments_from_function(body);

				ExtractedFunction * function = new ExtractedFunction (name, body, args, retval);
				functions.push_back(function);

				pos = pos_end_function;

				cnt++;
				cout<< endl<< "-!- FOUND -!-"<<endl;
				cout<< "LINE: " << pos_name<<endl;
				cout << "FUNCTION NAME:  " +name<<endl;
				cout << body<<endl;


				break;
		    }
		    else if (( isspace(file_content.at(i))))
		    {
		    	pos++;
		    	continue;
		    }
		    else{
		    	break;
		    }
		  }


		j++;
		cout << endl<< cnt;
	}


}

