#include "Test.h"

void Test::chooseTest() {
	startTest("SampleTest.txt");
}

void Test::startTest(std::string filename) {
	testData.clear();
	getTestData(filename);
	for (auto item : testData) {

		std::cout << item.Question << std::endl;

		int number = 0;

		for (auto answer : item.Answers) {
			std::cout << ++number << " " << answer << std::endl;
		}

		std::cout << std::endl;
	}
}

void Test::getTestData(std::string filename) {

	std::string currentQuestionString;

	std::ifstream input;
	input.open(filename);

	int query;
	input >> query;
	getline(input, currentQuestionString);

	for (int i = 0; i < query; ++i) {

		getline(input, currentQuestionString);

		testData.push_back(decodeQuestionString(currentQuestionString));
	}
}

TestModel Test::decodeQuestionString(std::string questionString) {
	TestModel result;
	std::string question, temp;
	int pos = 0;


	//		find question
	//----------------------------------
	for (auto symbol : questionString) {
		pos++;
		if (symbol == '$') break;
		question += symbol;
	}

	result.Question = question;
	//-----------------------------------

	//      find number of answers
	//-------------------------------------
	int numberAnswers = questionString[pos] - '0';
	//-------------------------------------

	//		find answers
	//-----------------------------------------------------
	pos += 2;
	for (int i = pos; i < questionString.size(); ++i) {
		pos++;
		if (questionString[i] == '$') {
			result.Answers.push_back(temp);
			temp.clear();
			numberAnswers--;
			if (numberAnswers == 0) break;
		}
		else {
			temp += questionString[i];
		}
	}
	//-----------------------------------------------------

	//		  find number of correct answers
	//-----------------------------------------------------
	pos++;
	int numberCorrectAnswers = questionString[pos] - '0';
	//-----------------------------------------------------	

	//			  find correct answers
	//-----------------------------------------------------
	pos += 1;
	for (int i = pos; i < questionString.size(); ++i) {
		if (questionString[i] != '$') {
			result.CorrectAnswers.push_back(questionString[i] - '0');
			numberCorrectAnswers--;
			if (numberCorrectAnswers == 0) break;
		}
	}
	//-----------------------------------------------------

	return result;
}