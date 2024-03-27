#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixop = 5 };

struct stQuestion {
	short number1 = 0;
	short number2 = 0;
	enQuestionLevel questionlevel;
	enOperationType operationType;
	short correctAnswer = 0;
	short playerAnswer = 0;
	bool answerResult = false;
};

struct stQuizz {
	short numberOfQuestions;
	stQuestion questionsList[100];
	enQuestionLevel questionsLevel;
	enOperationType operationsType;
	short numberOfCorrectAnswers = 0;
	short numberOfWrongAnsers = 0;
	bool isPass = false;
};

int randomNumber(int from, int to) {
	int randomNum = rand() % (to - from + 1) + from;
	return randomNum;
}

string getStringQuestionsLevel(enQuestionLevel level) {
	string levels[4] = { "Easy", "Mediam", "Hard", "Mix" };
	return levels[level - 1];
}

short getNumbersOfQuestions() {
	short numberOfQuestoins = 0;
	do {
		cout << "Enter The Number of Questions ? 1 to 10" << endl;
		cin >> numberOfQuestoins;
	} while (numberOfQuestoins < 1 || numberOfQuestoins > 10);
	return numberOfQuestoins;
}

enQuestionLevel getQuestionsLevel() {
	short questionsLevel = 0;
	do {
		cout << "Enter Questions Level [1] Easy , [2] Mediam , [3] Hard , [4] Mix " << endl;
		cin >> questionsLevel;
	} while (questionsLevel < 1 || questionsLevel > 4);
	return (enQuestionLevel)questionsLevel;
}

enOperationType getOperationsType() {
	short operationsType = 0;
	do {
		cout << "Enter Operations Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix" << endl;
		cin >> operationsType;
	} while (operationsType < 1 || operationsType > 5);
	return (enOperationType)operationsType;
}

string getSymbleOperation(enOperationType operation) {
	switch (operation) {
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	case enOperationType::Mixop:
		return "Mix";
	default:
		return "+";
	}

}

short getCorrectAnswer(short number1, short number2, enOperationType operationType) {
	switch (operationType) {
	case enOperationType::Add:
		return number1 + number2;
	case enOperationType::Sub:
		return number1 - number2;
	case enOperationType::Mul:
		return number1 * number2;
	case enOperationType::Div:
		return number1 / number2;
	default:
		return number1 + number2;
	}
}

short getPlayerAnswer() {
	short number;
	cin >> number;
	return number;
}

void setColorScreen(bool answer) {
	if (answer) {
		system("color 2F");
	}
	else {
		system("color 4F");
		cout << "\a";
	}
}

void isPASS(bool answer) {
	if (answer) {
		cout << "Congratulations (^_^) !!! You are Passed" << endl;
		system("color 2F");
	}
	else {
		cout << "You are Failed (-_-)" << endl;
		system("color 4F");
		cout << "\a" << endl;
	}
}

void isCorrectAnswer(stQuizz& quizz, short questionIndex) {
	if (quizz.questionsList[questionIndex].correctAnswer != quizz.questionsList[questionIndex].playerAnswer) {
		cout << endl;
		cout << "This is Wrong Answer (-_-)" << endl;
		cout << "The Right Answer Is : " << quizz.questionsList[questionIndex].correctAnswer << endl;
		quizz.questionsList[questionIndex].answerResult = false;
		quizz.numberOfWrongAnsers++;
	}
	else {
		cout << endl;
		cout << "This is Right Answer (^_^)" << endl;
		quizz.questionsList[questionIndex].answerResult = true;
		quizz.numberOfCorrectAnswers++;
	}
	setColorScreen(quizz.questionsList[questionIndex].answerResult);
}

stQuestion genrateQuestion(enQuestionLevel questionLevel, enOperationType operationType) {
	stQuestion question;

	if (questionLevel == enQuestionLevel::Mix) {
		questionLevel = (enQuestionLevel)randomNumber(1, 3);
	}

	if (operationType == enOperationType::Mixop) {
		operationType = (enOperationType)randomNumber(1, 4);
	}

	question.operationType = operationType;

	switch (questionLevel) {
	case enQuestionLevel::Easy:
		question.number1 = randomNumber(1, 10);
		question.number2 = randomNumber(1, 10);
		question.correctAnswer = getCorrectAnswer(question.number1, question.number2, question.operationType);
		question.questionlevel = questionLevel;
		return question;

	case enQuestionLevel::Mid:
		question.number1 = randomNumber(10, 50);
		question.number2 = randomNumber(10, 50);
		question.correctAnswer = getCorrectAnswer(question.number1, question.number2, question.operationType);
		question.questionlevel = questionLevel;
		return question;

	case enQuestionLevel::Hard:
		question.number1 = randomNumber(50, 100);
		question.number2 = randomNumber(50, 100);
		question.correctAnswer = getCorrectAnswer(question.number1, question.number2, question.operationType);
		question.questionlevel = questionLevel;
		return question;

	}
	return question;
}


void genrateQuestionsList(stQuizz& quizz) {

	for (short questionIndex = 0; questionIndex < quizz.numberOfQuestions; questionIndex++) {
		quizz.questionsList[questionIndex] = genrateQuestion(quizz.questionsLevel, quizz.operationsType);
	}

}


void printQuestion(stQuizz& quizz, short questionIndex) {

	cout << "\n\n";
	cout << "---------- Qusetion [" << questionIndex + 1 << " / " << quizz.numberOfQuestions << "] ----------\n";
	cout << quizz.questionsList[questionIndex].number1 << endl;
	cout << quizz.questionsList[questionIndex].number2;
	cout << "    " << getSymbleOperation(quizz.questionsList[questionIndex].operationType) << endl;
	cout << "---------------\n\n";
}

void AskAndCorrectQuestionslistAnswers(stQuizz& quizz) {
	for (short questionIndex = 0; questionIndex < quizz.numberOfQuestions; questionIndex++) {

		printQuestion(quizz, questionIndex);

		quizz.questionsList[questionIndex].playerAnswer = getPlayerAnswer();

		isCorrectAnswer(quizz, questionIndex);

	}
}

void printFinialResult(stQuizz quizz) {
	cout << "\n\n";
	cout << "-----------------------------------------\n";
	cout << "----------- The Finial Result -----------" << endl;
	cout << "The Number Of Questions is       : " << quizz.numberOfQuestions << endl;
	cout << "The Level Of Questions is        : " << getStringQuestionsLevel(quizz.questionsLevel) << endl;
	cout << "The Number Of Wrong Answers is   :" << quizz.numberOfWrongAnsers << endl;
	cout << "The Number of Correct Answers is :" << quizz.numberOfCorrectAnswers << endl;
	isPASS(quizz.numberOfCorrectAnswers > quizz.numberOfWrongAnsers);

}

void playMathGame() {

	stQuizz quizz;

	quizz.numberOfQuestions = getNumbersOfQuestions();
	quizz.questionsLevel = getQuestionsLevel();
	quizz.operationsType = getOperationsType();

	genrateQuestionsList(quizz);
	AskAndCorrectQuestionslistAnswers(quizz);
	printFinialResult(quizz);

}

void restScreen() {
	system("cls");
	system("color 0F");
}

void startGame() {

	char playMore = 'y';
	do {
		restScreen();
		playMathGame();
		cout << "---------------------------------------\n";
		cout << "Do You Want To Play More ? ( Y / N ) ? \n" << endl;
		cin >> playMore;

	} while (playMore == 'y' || playMore == 'Y');


}

int main() {
	srand((unsigned)time(NULL));

	startGame();


	return 0;
}