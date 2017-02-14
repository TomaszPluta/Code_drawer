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
#include <string>
#include <vector>

/*local includes*/
#include "../src/Code_drawer.h"
#include "../src/function_extractor.h"

using namespace std;


TEST(InitGoogleMockTest, test_extract_function_from_file) {

	ofstream sample_file_on_disc;
	sample_file_on_disc.open("sample_file.c");
	sample_file_on_disc << "called_method();"
			"struct{int a = 0}; "
			"void foo(){"
			"method_l1a()"
			"method_l1b()"
			"method_l1c()"
			"}";
	sample_file_on_disc.close();

	FileToDraw sample_file ;
	sample_file.open("sample_file.c");
	sample_file.parse();
//	string foo_body = sample_file.get_function("foo");


//	string expected_result("void foo(){"
//			"method_l1a()"
//			"method_l1b()"
//			"method_l1c()"
//			"}");
//	EXPECT_STREQ(foo_body.c_str(), expected_result.c_str());
}

//
//TEST(InitGoogleMockTest, test_extract_desired_function_from_file) {
//
//	ofstream sample_file;
//	sample_file.open("sample_file.c");
//	sample_file << "called_method();"
//			"struct{int a = 0}; "
//			"void foo(){"
//			"method_l1a();"
//			"int x;"
//			"method_l1b();"
//			"method_l1c();"
//			"}; "
//			"int main(){"
//			"method_l1d();"
//			"int x;"
//			"method_l1e();"
//			"method_l1f();"
//			"};";
//	sample_file.close();
//	string expected_result("int main(){"
//			"method_l1d();"
//			"int x;"
//			"method_l1e();"
//			"method_l1f();"
//			"};");
//
//	string method;
//	method = extract_functions("sample_file.c", "main");
//	EXPECT_STREQ(method.c_str(), expected_result.c_str());
//};






//
//TEST(InitGoogleMockTest, test_find_called) {
//
//	ofstream sample_file;
//	sample_file.open("sample_file.c");
//	sample_file << "called_method();"
//			"struct{int a = 0}; "
//			"void foo(){"
//			"method_l1a()"
//			"method_l1b()"
//			"method_l1c()"
//			"}; ";
//	sample_file.close();
//	vector  <string> expected_called;
//	expected_called.push_back("method_l1a");
//	expected_called.push_back("method_l1b");
//	expected_called.push_back("method_l1c");
//	const int expected_called_count = 3;
//
//	vector  <string> finded_called = find_called("sample_file.c", "foo");
//	ASSERT_TRUE(finded_called.size() == expected_called_count);
//	EXPECT_STREQ(finded_called[0].c_str(), expected_called[0].c_str());
//	EXPECT_STREQ(finded_called[1].c_str(), expected_called[1].c_str());
//	EXPECT_STREQ(finded_called[2].c_str(), expected_called[2].c_str());
//};




#ifdef test

int main(int argc, char* argv[]) {
	cout << "run test!" << endl;


	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}

#endif
