#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

enum enLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4};
enum enOpType { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, Mix = 5 };

struct stQuizz
{
	short QuestionNumber = 0;
	enLevel Level;
	enOpType OpType;
	short NumberOfQuestions = 0;
};

struct stGameResults
{
	short NumberOfQuestions = 0;
	short RightAnswersNumber = 0;
	short WrongAnswersNumber = 0;
	enLevel Level;
	string LevelName = "";
	enOpType OpType;
	string OpTypeName = "";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enLevel ReadLevel()
{
	short Level;
	do
	{
		cout << "\nEnter questions level: [1]:Easy, [2]:Mid, [3]:Hard, [4]:Mix? ";
		cin >> Level;
	} while ( Level < 1 || Level > 4);

	return (enLevel)Level;
}

enOpType ReadOpType()
{
	short OpType;
	do
	{
		cout << "\nEnter operation type: [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOpType)OpType;
}

string LevelName(enLevel Level)
{
	string arr[4] = { "Easy", "Mid", "Hard", "Mix" };
	return arr[Level - 1];
}

string OpTypeName(enOpType OpType)
{
	string arr[5] = { "Addition", "Subtraction", "Multiplication", "Division", "Mix" };
	return arr[OpType - 1];
}

stQuizz ReadQuizzInfo(stQuizz &Quizz)
{
	cout << "How many questions do you want to answer?";
	cin >> Quizz.NumberOfQuestions;

	Quizz.Level = ReadLevel();
	Quizz.OpType = ReadOpType();

	return Quizz;
}

int GenerateNumber(enLevel Level)
{
	switch (Level)
	{
	case enLevel::Easy:
		return RandomNumber(1, 10);
	case enLevel::Mid:
		return RandomNumber(11, 50);
	case enLevel::Hard:
		return RandomNumber(51, 100);
	case enLevel::Mix:
		return RandomNumber(1, 100);
	}
}

char OpTypeSymbol(enOpType OpType)
{
	switch (OpType)
	{
	case enOpType::Addition:
		return '+';
	case enOpType::Subtraction:
		return '-';
	case enOpType::Multiplication:
		return '*';
	case enOpType::Division:
		return '/';
	}
}

void PrintQuizzResults(stGameResults GameResults)
{
	GameResults.LevelName = LevelName(GameResults.Level);
	GameResults.OpTypeName = OpTypeName(GameResults.OpType);

	cout << "\n__________________________________\n";
	cout << "Final Result is ";
	cout << "\n__________________________________\n";

	cout << "\nNumber Of Questions:		" << GameResults.NumberOfQuestions;
	cout << "\nQuestions Level:			" << GameResults.LevelName;
	cout << "\nOpType:					" << GameResults.OpTypeName;
	cout << "\nNumber Of Right Answers: " << GameResults.RightAnswersNumber;
	cout << "\nNumber Of Wrong Answers:	" << GameResults.WrongAnswersNumber;

	cout << "\n__________________________________\n";

}

stGameResults PlayMathGame()
{
	stQuizz Quizz;
	ReadQuizzInfo(Quizz);

	for (int QuestionNumber = 1; QuestionNumber <= Quizz.NumberOfQuestions; QuestionNumber++)
	{
		cout << "Question [" << QuestionNumber << "/" << Quizz.NumberOfQuestions << "]" << endl;

		cout << endl;
		cout << GenerateNumber(Quizz.Level) << endl;
		cout << GenerateNumber(Quizz.Level) << " ";
		cout << OpTypeSymbol(Quizz.OpType);
		cout << "\n__________________________________\n";
	}
}

int main()
{
	srand((unsigned)time(NULL));
}