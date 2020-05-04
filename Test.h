#include <string>
#include <vector>
#include "TestModel.h"
#include <fstream>
#include <iostream>

class Test {

private:	
	std::vector<TestModel> testData;
	void getTestData(std::string);
	TestModel decodeQuestionString(std::string);
public:
	void chooseTest();
	void startTest(std::string);
};
