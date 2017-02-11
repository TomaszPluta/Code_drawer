//============================================================================
// Name        : Code_drawer.cpp
// Author      : tomaszp
// Version     :
//======================================================================

#include <iostream>
#include <fstream>
#include "method_extractor.h"

using namespace std;

//#define release

#ifdef release
int main() {

	ofstream sample_file;
	sample_file.open("sample_file.c");
	sample_file << "called_method();"
			"struct{int a = 0}; "
			"void foo(){"
			"method_l1a()"
			"method_l1b()"
			"method_l1c()"
			"};";
	sample_file.close();

	extract_method("sample_file.c");
}

#endif
