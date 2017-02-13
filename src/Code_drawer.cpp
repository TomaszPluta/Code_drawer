//============================================================================
// Name        : Code_drawer.cpp
// Author      : tomaszp
// Version     :
//======================================================================

#include <iostream>
#include <fstream>

/*local includes*/
#include "Code_drawer.h"
#include "function_extractor.h"

using namespace std;



#ifndef test
int main() {

	ofstream sample_file;
	sample_file.open("sample_file.c");
	sample_file << "called_method();"
			"struct{int a = 0}; "
			"void foo(){"
			"method_l1a()"
			"method_l1b()"
			"method_l1c()"
			"}; "
			"int main(){ "
			"method_l1d(arg1) "
			"int x; "
			"method_l1e() "
			"method_l1f() "
			"};";
	sample_file.close();

	FileToDraw sample;
	sample.open("sample_file.c");
	sample.parse();

//	extract_functions("sample_file.c", "main");
//	find_called("sample_file.c", "main");
}

#endif
