/*
 * test_main.cpp
 *
 *  Created on: 29 sty 2017
 *      Author: tomek
 */




//============================================================================
// Name        : Code_drawer.cpp
// Author      : tomaszp
//============================================================================

#include <iostream>
#include <fstream>
#include "../gmock/gmock/gmock.h"
#include "../gmock/gtest/gtest.h"
#include "string.h"

/*local includes*/
#include	"method_extractor.h"

using namespace std;


TEST(InitGoogleMockTest, test_extract_metod_from_file) {

	ofstream sample_file;
	sample_file.open("sample_file.c");
	sample_file << "called_method();"
			"struct{int a = 0}; "
			"void foo(){"
			"	here_we_are()"
			"};";
	sample_file.close();
	string expected_result("void foo(){"
			")here_we_are()"
			"};");

	string method;
	method = extract_method("sample_file.c");
	EXPECT_STREQ(method.c_str(), expected_result.c_str());
};


#define test 1
#ifdef test

int main(int argc, char* argv[]) {
	cout << "run test!" << endl;


	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}

#endif
