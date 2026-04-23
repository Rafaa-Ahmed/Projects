#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRounds()
{
    short RoundsNumber = 0;
    do
    {
        cout << "How Many Rounds (1 To 10) ? " << endl;
        cin >> RoundsNumber;
    } while (RoundsNumber < 1 || RoundsNumber > 10);
    return RoundsNumber;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }

    return enWinner::Draw; // ✅ added
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "___________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

string Tabs(short NumberOfTabs) {
    string t = "";
    for (int i = 1; i <= NumberOfTabs; i++)
    {
        t += "\t";
    }
    return t;
}

void ShowFinalGameResults(stGameResults GameResult) {
    cout << Tabs(2) << "--------------------------------[Game Result]----------------------------" << endl;
    cout << Tabs(2) << "Game Rounds        : " << GameResult.GameRounds << endl;
    cout << Tabs(2) << "Player1 Win Times  : " << GameResult.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Win Times : " << GameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times         : " << GameResult.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResult.WinnerName << endl;

    SetWinnerScreenColor(GameResult.GameWinner);
}

stGameResults FillGameResults(short GameRound, short Player1wintimes, short Computerwintimes, short Drawstimes)
{
    stGameResults GameResult;

    GameResult.GameRounds = GameRound;
    GameResult.Player1WinTimes = Player1wintimes;
    GameResult.ComputerWinTimes = Computerwintimes;
    GameResult.DrawTimes = Drawstimes;
    GameResult.GameWinner = WhoWonTheGame(Player1wintimes, Computerwintimes);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "-------------------------------------------------------------------------\n\n";
    cout << Tabs(5) << "   +++ G a m e O v e r +++\n\n";
    cout << Tabs(2) << "-------------------------------------------------------------------------\n\n";
}

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << endl << Tabs(3) << "Do You Want To Play Again Y/N ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}