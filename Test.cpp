#include "Test.h"
#include "TestController.h"

void Test::startApp() {
	std::cout << "1. Choose the test." << std::endl;
	std::cout << "2. Create the test." << std::endl;
	std::cout << "3. Erase the test." << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "Enter number which you need to execute: ";
	
	int result;
	while ((result = getNumber(1, 3)) == -1) {
		std::cout << "Please enter the correct number: ";
	}

	switch (result) {
		case 1: {
			system("cls");
			chooseTest();
			break;
		}
		case 2: {
			system("cls");
			createTest();
			break;
		}
		case 3: {
			system("cls");
			chooseTestToErase();
			break;
		}
		default: {
			exit(0);
		}
	}
}

void Test::createTest() {
	std::string nameTest;
	int numberQuestions;
	std::ofstream dataTest;

	std::cout << "Enter the name of your test: ";
	std::cin >> nameTest;

	TestController::addNewTest(nameTest + ".txt");
	dataTest.open(nameTest + ".txt");

	std::cout << "Enter number of questions: ";

	while ((numberQuestions = getNumber(1, 100)) == -1) {
		std::cout << "Enter correct number(1, 100): ";
	}

	dataTest << numberQuestions << std::endl;

	for (int indexQuestion = 0; indexQuestion < numberQuestions; ++indexQuestion) {
		TestModel currentQuestion;
		int numberAnswers;
		int numberCorrectAnswers;

		std::cout << "Enter the question #" << indexQuestion + 1 << ": ";

		getline(std::cin, currentQuestion.Question);
		getline(std::cin, currentQuestion.Question);

		std::cout << "Enter the number of answers: ";
		while ((numberAnswers = getNumber(1, 100)) == -1) {
			std::cout << "Enter the correct number(1, 100): ";
		}

		for (int indexAnswer = 0; indexAnswer < numberAnswers; ++indexAnswer) {
			std::string answer;
			std::cout << "Enter the " << indexAnswer + 1 << " answer: ";
			std::cin >> answer;
			currentQuestion.Answers.push_back(answer);
		}

		std::cout << "Enter the number of correct answers: ";
		while ((numberCorrectAnswers = getNumber(1, numberAnswers)) == -1) {
			std::cout << "Enter the correct number(1," << numberAnswers << "): ";
		}

		for (int indexCorrectAnswer = 0; indexCorrectAnswer < numberCorrectAnswers; ++indexCorrectAnswer) {
			int correctAnswer;
			std::cout << "Enter the index of correct answer: ";

			while ((correctAnswer = getNumber(1, numberAnswers)) == -1) {
				std::cout << "Enter the correct number(1," << numberAnswers << "): ";
			}
			
			currentQuestion.CorrectAnswers.push_back(correctAnswer);
		}

		dataTest << encryptQuestionObject(currentQuestion) << std::endl;
		system("cls");
	}

	this->startApp();
}

void Test::chooseTest() {
	std::vector <std::string> tests = TestController::getTestList();

	int number = 1;

	for (auto item : tests) {
		std::cout << number++ << " - " << item << std::endl;
	}


	std::cout << "Please choose the test: " << std::endl;

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

void Test::chooseTestToErase() {
	std::vector <std::string> tests = TestController::getTestList();

	int number = 1;

	for (auto item : tests) {
		std::cout << number++ << " - " << item << std::endl;
	}


	std::cout << "Please enter index of test which you need to delete, or enter 0 to back in main menu: " << std::endl;

	int answer;

	while ((answer = getNumber(1, tests.size())) == -1) {
		std::cout << "Please enter the correct number: ";
	}

	if (answer == 0) {
		system("cls");
		this->startApp();
		return;
	}
	
	TestController::eraseTest(tests[answer - 1]);
	system("cls");
	this->startApp();
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

	std::cout << "Please enter 1 if you want go to main menu, or 2 if you want to exit" << std::endl;
	int resultUserAction;

	while ((resultUserAction = this->getNumber(1, 2)) == -1) {
		std::cout << "Please enter the correct number: ";
	}
	if (resultUserAction == 1) {
		system("cls");
		this->startApp();
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


std::string Test::encryptQuestionObject(TestModel question) {
	std::string result;

	//question
	result += question.Question + "$";

	//number answers
	result += std::to_string(question.Answers.size()) + "$";

	//answers
	for (auto item : question.Answers) result += item + "$";

	//number of correct answers
	result += std::to_string(question.CorrectAnswers.size()) + "$";

	//correct answers
	for (auto item : question.CorrectAnswers) {
		result += std::to_string(item) + "$";
	}

	result.erase(result.size() - 1);

	return result;
}

TestModel Test::decodeQuestionString(std::string questionString) {

	TestModel result;
	std::string question, temp;
	int pos = 0;
	
	//find question
	for (auto symbol : questionString) {
		pos++;
		if (symbol == '$') break;
		question += symbol;
	}
	result.Question = question;

	//find number of answers
	int numberAnswers = questionString[pos] - '0';

	//find answers
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

	//find number of correct answers
	pos++;
	int numberCorrectAnswers = questionString[pos] - '0';

	//find correct answers
	pos += 1;
	for (int i = pos; i < questionString.size(); ++i) {
		if (questionString[i] != '$') {
			result.CorrectAnswers.push_back(questionString[i] - '0');
			numberCorrectAnswers--;
			if (numberCorrectAnswers == 0) break;
		}
	}
	std::sort(result.CorrectAnswers.begin(), result.CorrectAnswers.end());

	return result;
}