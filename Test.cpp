#include "Test.h"
#include "TestController.h"

void Test::chooseTest() {
	std::vector <std::string> tests = TestController::getTestList();

	int number = 1;

	std::cout << "Please choose test: " << std::endl;

	for (auto item : tests) {
		std::cout << number++ << " - " << item << std::endl;
	}

	int answer;

	while ((answer = getNumber(1, tests.size())) == -1) {
		std::cout << "Please enter the correct number: ";
	}

	system("cls");
	startTest(tests[answer - 1]);
}

int Test::getNumber(int leftBorder, int rightBorder) {
	std::string current;
	int result = -1;

	std::cin >> current;
	try {
		result = stoi(current);
		if (!(leftBorder <= result && result <= rightBorder)) {
			result = -1;
		}
	}
	catch (std::invalid_argument) {
		result = -1;
	}

	return result;
}

void Test::startTest(std::string filename) {
	testData.clear();
	getTestData(filename); 

	int resultPoints = 0;
	int numberQuestion = 0;

	for (auto item : testData) {
		
		std::cout << "Question is " << ++numberQuestion << "/" << testData.size() << std::endl;
		std::cout << item.Question << std::endl;

		int number = 0;
		for (auto answer : item.Answers) {
			std::cout << ++number << " " << answer << std::endl;
		}
		std::cout << std::endl;

		std::string stringNumberAnswers;
		std::cout << "Please enter a number of answers which you think is correct: ";

		int numberAnswers;
		while ((numberAnswers = this->getNumber(1, item.Answers.size())) == -1) {
			std::cout << "Please enter the correct number: ";
		}

		std::vector <int> userAnswers;

		for (int i = 0; i < numberAnswers; ++i) {
			int nextValue;

			if (i == 0) {
				std::cout << "Please enter answer which you think is correct: ";
			}
			else {
				std::cout << "Enter next answer: ";
			}
			
			while ((nextValue = this->getNumber(1, item.Answers.size())) == -1) {
				std::cout << "Please enter the correct answer: ";
			}
			
			userAnswers.push_back(nextValue);
		}

		std::sort(userAnswers.begin(), userAnswers.end());
		std::unique(userAnswers.begin(), userAnswers.end());

		if (userAnswers == item.CorrectAnswers) {
			resultPoints += 1;
		}

		system("cls");
	}

	double result = resultPoints / (testData.size() + 0.0);

	std::cout << "You passed test by " << std::fixed << std::setprecision(2) << result * 100 << "%." << std::endl;

	std::cout << "Please enter 1 if you want another test, or 2 if you want to exit" << std::endl;
	int resultUserAction;

	while ((resultUserAction = this->getNumber(1, 2)) == -1) {
		std::cout << "Please enter the correct number: ";
	}
	if (resultUserAction == 1) {
		system("cls");
		this->chooseTest();
	}
	else {
		exit(0);
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

	input.close();
}

TestModel Test::decodeQuestionString(std::string questionString) {

	TestModel result;
	std::string question, temp;
	int pos = 0;
	
	//find question
	//----------------------------------
	for (auto symbol : questionString) {
		pos++;
		if (symbol == '$') break;
		question += symbol;
	}
	result.Question = question;
	//-----------------------------------

	//find number of answers
	//-------------------------------------
	int numberAnswers = questionString[pos] - '0';
	//-------------------------------------

	//find answers
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

	//find number of correct answers
	//-----------------------------------------------------
	pos++;
	int numberCorrectAnswers = questionString[pos] - '0';
	//-----------------------------------------------------	

	//find correct answers
	//-----------------------------------------------------
	pos += 1;
	for (int i = pos; i < questionString.size(); ++i) {
		if (questionString[i] != '$') {
			result.CorrectAnswers.push_back(questionString[i] - '0');
			numberCorrectAnswers--;
			if (numberCorrectAnswers == 0) break;
		}
	}
	std::sort(result.CorrectAnswers.begin(), result.CorrectAnswers.end());
	//-----------------------------------------------------

	return result;
}