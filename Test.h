#include <string>
#include <vector>
#include "TestModel.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <iomanip>

class Test {

private:	
	std::vector<TestModel> getTestData(std::string);
	TestModel decodeQuestionString(std::string);
	std::string encryptQuestionObject(TestModel);
	int getNumber(int, int);
	TestModel getTestQuestion();
	void fromObjectToFile(std::string, std::vector<TestModel>);
public:
	void createTest();
	void startApp();
	void chooseTest(std::string);
	void startTest(std::string);
	void startEdit(std::string);
};

