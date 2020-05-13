#include "Test.h"

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
	int numberAnswers = 0;
	temp.clear();
	
	for (int i = pos; i < questionString.size(); ++i) {
		if (questionString[i] == '$') break;
		temp += questionString[i];
		pos++;
	}

	numberAnswers = stoi(temp);

	//find answers
	pos++;
	temp.clear();
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
	int numberCorrectAnswers = 0;
	temp.clear();

	for (int i = pos; i < questionString.size(); ++i) {
		if (questionString[i] == '$') break;
		temp += questionString[i];
		pos++;
	}

	numberCorrectAnswers = stoi(temp); 

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