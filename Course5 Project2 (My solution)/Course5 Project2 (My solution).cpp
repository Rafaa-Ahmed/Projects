#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOpType { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, Mixed = 5 };

struct stQuizz
{
    enLevel Level;
    enOpType OpType;
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

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

enLevel ReadLevel()
{
    short Level;
    do
    {
        cout << "\nEnter questions level: [1]:Easy, [2]:Mid, [3]:Hard, [4]:Mix? ";
        cin >> Level;
    } while (Level < 1 || Level > 4);

    return (enLevel)Level;
}

enOpType ReadOpType()
{
    short OpType;
    do
    {
        cout << "\nEnter operation type: [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mixed? ";
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
    string arr[5] = { "Addition", "Subtraction", "Multiplication", "Division", "Mixed" };
    return arr[OpType - 1];
}

short ReadNumberOfQuestions()
{
    short NumberOfQuestions;
    cout << "How many questions do you want to answer? ";
    cin >> NumberOfQuestions;
    return NumberOfQuestions;
}

void ReadQuizzInfo(stQuizz& Quizz)
{
    Quizz.Level = ReadLevel();
    Quizz.OpType = ReadOpType();
}

int GenerateNumber(enLevel Level)
{
    switch (Level)
    {
    case Easy: return RandomNumber(1, 10);
    case Mid: return RandomNumber(11, 50);
    case Hard: return RandomNumber(51, 100);
    case Mix: return RandomNumber(1, 100);
    default: return 0;
    }
}

char OpTypeSymbol(enOpType OpType)
{
    switch (OpType)
    {
    case Addition: return '+';
    case Subtraction: return '-';
    case Multiplication: return '*';
    case Division: return '/';
    default: return '?';
    }
}

int CalculateAnswer(enOpType OpType, int Number1, int Number2)
{
    switch (OpType)
    {
    case Addition: return Number1 + Number2;
    case Subtraction: return Number1 - Number2;
    case Multiplication: return Number1 * Number2;
    case Division:
        if (Number2 == 0) Number2 = 1;
        return Number1 / Number2;
    default: return 0;
    }
}

bool CheckAnswer(int Answer, int RightAnswer)
{
    return (Answer == RightAnswer);
}

stGameResults FillGameResults(short NumberOfQuestions, enLevel Level, enOpType OpType, short RightAnswersNumber, short WrongAnswersNumber)
{
    stGameResults GameResult;

    GameResult.NumberOfQuestions = NumberOfQuestions;
    GameResult.Level = Level;
    GameResult.LevelName = LevelName(Level);
    GameResult.OpType = OpType;
    GameResult.OpTypeName = OpTypeName(OpType);
    GameResult.RightAnswersNumber = RightAnswersNumber;
    GameResult.WrongAnswersNumber = WrongAnswersNumber;

    return GameResult;
}

void ShowFinalResults(stGameResults GameResults)
{
    if (GameResults.RightAnswersNumber >= GameResults.WrongAnswersNumber)
    {
        cout << "Final Result is PASS :-)";
        system("color 2F");
    }
    else
    {
        cout << "Final Result is FAIL :-(";
        system("color 4");
    }
}

void PrintQuizzResults(stGameResults GameResults)
{
    cout << "\n\n__________________________________\n";
    ShowFinalResults(GameResults);
    cout << "\n__________________________________\n";

    cout << "\nNumber Of Questions: " << GameResults.NumberOfQuestions;
    cout << "\nQuestions Level: " << GameResults.LevelName;
    cout << "\nOpType: " << GameResults.OpTypeName;
    cout << "\nRight Answers: " << GameResults.RightAnswersNumber;
    cout << "\nWrong Answers: " << GameResults.WrongAnswersNumber;

    cout << "\n__________________________________\n";
}

stGameResults PlayMathGame(short NumberOfQuestions)
{
    stQuizz Quizz;
    ReadQuizzInfo(Quizz);

    short RightAnswersNumber = 0;
    short WrongAnswersNumber = 0;

    for (int QuestionNumber = 1; QuestionNumber <= NumberOfQuestions; QuestionNumber++)
    {
        cout << "\nQuestion [" << QuestionNumber << "/" << NumberOfQuestions << "]\n";

        int Number1 = GenerateNumber(Quizz.Level);
        int Number2 = GenerateNumber(Quizz.Level);

        enOpType CurrentOp = Quizz.OpType;
        if (CurrentOp == Mixed)
            CurrentOp = (enOpType)RandomNumber(1, 4);

        cout << "\n" << Number1 << endl;
        cout << Number2 << " " << OpTypeSymbol(CurrentOp);
        cout << "\n__________________________________\n";

        int Answer;
        cin >> Answer;

        int RightAnswer = CalculateAnswer(CurrentOp, Number1, Number2);

        if (CheckAnswer(Answer, RightAnswer))
        {
            cout << "\nRight Answer :-)\n";
            system("color 2F");
            RightAnswersNumber++;
        }
        else
        {
            cout << "\nWrong Answer :-(\n";
            cout << "The right answer is " << RightAnswer << endl;
            system("color 4F");
            cout << "\a";
            WrongAnswersNumber++;
        }
    }

    return FillGameResults(NumberOfQuestions, Quizz.Level, Quizz.OpType,
        RightAnswersNumber, WrongAnswersNumber);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();

        stGameResults GameResults = PlayMathGame(ReadNumberOfQuestions());
        PrintQuizzResults(GameResults);

        cout << endl << "Do You Want To Play Again Y/N ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}