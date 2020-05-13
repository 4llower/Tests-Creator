#include "TestData.h"

std::vector<std::string> TestData::getTestList() {
	std::ifstream input;
	input.open("AllTests.txt");

	std::vector <std::string> result;

	int query;
	input >> query;

	for (int i = 0; i < query; ++i) {
		std::string temp;
		input >> temp;
		result.push_back(temp);
	}

	input.close();
	return result;
}

void TestData::addNewTest(std::string nameTest){
	std::vector <std::string> tests = getTestList();
	tests.push_back(nameTest);

	std::ofstream output;
	output.open("AllTests.txt");

	output << tests.size() << std::endl;
	for (auto item : tests) {
		output << item << std::endl;
	}

	output.close();
}

void TestData::eraseTest(std::string nameTest) {
	std::vector <std::string> tests = getTestList();

	for (auto it = tests.begin(); it != tests.end(); ++it) {
		if (*it == nameTest) {
			tests.erase(it);
			break;
		}
	}

	std::ofstream output;
	output.open("AllTests.txt");

	output << tests.size() << std::endl;
	for (auto item : tests) {
		output << item << std::endl;
	}

	output.close();
}
