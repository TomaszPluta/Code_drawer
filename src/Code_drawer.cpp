//============================================================================
// Name        : Code_drawer.cpp
// Author      : tomaszp
// Version     :
//======================================================================

#include <iostream>
#include <fstream>
#include "method_extractor.h"

using namespace std;

#define release 1

#ifdef release
int main() {

	ofstream sample_file;
	sample_file.open("sample_file.c");
	sample_file << "called_method();"
			"struct{int a = 0}; "
			"void foo(){"
			"here_we_are()"
			"};";
	sample_file.close();

	extract_method("sample_file.c");
}

#endif
