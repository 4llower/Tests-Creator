#include "Test.h"
#include "TestData.h"

void Test::startApp() {
	std::cout << "1. Choose the test." << std::endl;
	std::cout << "2. Create the test." << std::endl;
	std::cout << "3. Erase the test." << std::endl;
	std::cout << "4. Change the test" << std::endl;
	std::cout << "5. Exit" << std::endl;
	std::cout << "Enter number which you need to execute: ";
	
	int result;
	while ((result = getNumber(1, 5)) == -1) {
		std::cout << "Please enter the correct number: ";
	}

	switch (result) {
		case 1: {
			system("cls");
			chooseTest("Start");
			break;
		}
		case 2: {
			system("cls");
			createTest();
			break;
		}
		case 3: {
			system("cls");
			chooseTest("Delete");
			break;
		}
		case 4: {
			system("cls");
			chooseTest("Edit");
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

	TestData::addNewTest(nameTest + ".txt");
	dataTest.open(pathToTests + nameTest + ".txt");

	std::cout << "Enter number of questions: ";

	while ((numberQuestions = getNumber(1, 100)) == -1) {
		std::cout << "Enter correct number(1, 100): ";
	}

	dataTest << numberQuestions << std::endl;

	for (int indexQuestion = 0; indexQuestion < numberQuestions; ++indexQuestion) {
		std::cout << "Enter the question #" << indexQuestion + 1 << ": ";
		dataTest << encryptQuestionObject(getTestQuestion()) << std::endl;
		system("cls");
	}

	this->startApp();
}

void Test::fromObjectToFile(std::string filename, std::vector <TestModel> testData) {
	std::ofstream output;
	output.open(pathToTests + filename);
	
	output << testData.size() << std::endl;
	
	for (auto item : testData) {
		output << encryptQuestionObject(item) << std::endl;
	}

	output.close();
}

TestModel Test::getTestQuestion() {
	TestModel result;
	
	int numberAnswers;
	int numberCorrectAnswers;

	getline(std::cin, result.Question);
	getline(std::cin, result.Question);

	std::cout << "Enter the number of answers: ";
	while ((numberAnswers = getNumber(1, 100)) == -1) {
		std::cout << "Enter the correct number(1, 100): ";
	}

	for (int indexAnswer = 0; indexAnswer < numberAnswers; ++indexAnswer) {
		std::string answer;
		std::cout << "Enter the " << indexAnswer + 1 << " answer: ";
		std::cin >> answer;
		result.Answers.push_back(answer);
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

		result.CorrectAnswers.push_back(correctAnswer);
	}

	return result;
}

void Test::chooseTest(std::string action) {
	std::vector <std::string> tests = TestData::getTestList();

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

	if (action == "Start") {
		startTest(tests[answer - 1]);
		return;
	}

	if (action == "Delete") {
		TestData::eraseTest(tests[answer - 1]);
		this->startApp();
		return;
	}

	if (action == "Edit") {
		startEdit(tests[answer - 1]);
		return;
	}
}

void Test::startTest(std::string filename) {
	std::vector<TestModel> testData = getTestData(filename);

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

void Test::startEdit(std::string filename) {
	std::vector<TestModel> testData = getTestData(filename);
	int numberQuestion = 0;

	for (auto item : testData) {
		std::cout << "Question is " << ++numberQuestion << "/" << testData.size() << std::endl;
		std::cout << item.Question << std::endl;

		int number = 0;
		for (auto answer : item.Answers) {
			std::cout << ++number << " " << answer << std::endl;
		}

		std::cout << std::endl;
	}

	std::cout << "Enter the number of question which you need to edit or 0 to exit: ";

	int numberEdit = 0;
	while ((numberEdit = getNumber(0, testData.size())) == -1) {
		std::cout << "Enter the correct number(0," << testData.size() << "): ";
	}

	if (numberEdit == 0) {
		system("cls");
		this->startApp();
		return;
	}

	std::cout << "Enter the question: ";
	testData[numberEdit - 1] = getTestQuestion();

	fromObjectToFile(filename, testData);
	system("cls");
	this->startApp();
}


std::vector<TestModel> Test::getTestData(std::string filename) {

	std::vector<TestModel> testData;
	std::string currentQuestionString;

	std::ifstream input;
	input.open(pathToTests + filename);

	int query;
	input >> query;
	getline(input, currentQuestionString);

	for (int i = 0; i < query; ++i) {
		getline(input, currentQuestionString);
		testData.push_back(decodeQuestionString(currentQuestionString));
	}

	input.close();

	return testData;
}