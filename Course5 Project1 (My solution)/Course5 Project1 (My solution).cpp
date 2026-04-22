#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enRockPaperScissors { Rock = 1, Paper = 2, Scissors = 3 };

enRockPaperScissors RockPaperScissors(int Choice)
{
	if (Choice == 1)
		return enRockPaperScissors::Rock;

	if (Choice == 2)
		return enRockPaperScissors::Paper;

	if (Choice == 3)
		return enRockPaperScissors::Scissors;
	else
		return enRockPaperScissors::Rock;
}

string GetChoiceName(enRockPaperScissors Choice)
{
	switch (Choice)
	{
	case enRockPaperScissors::Rock:
		return "Rock";
	case enRockPaperScissors::Paper:
		return "Paper";
	case enRockPaperScissors::Scissors:
		return "Scissors";
	default:
		return "Unknown";
	}
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	
	return randNum;
}

int MaxNumber(int A, int B, int C)
{
	if (A >= B)
	{
		if (A >= C)
			return A;
		else
			return C;
	}

	else if (B >= C)
		return B;

	else
		return C;
}

int HowManyRounds()
{
	int Rounds;
	cout << "How many round do you want to play (1 to 10) ?" << endl;
	cin >> Rounds;

	return Rounds;
}

int UserChoice()
{
	int Choice;

	cout << "\nYour choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
	cin >> Choice;

	return Choice;
}

string RoundWinner(int PlayerChoice, int ComputerChoice)
{
	if (RockPaperScissors(PlayerChoice) == enRockPaperScissors::Rock)
	{
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Rock)
		{
			system("color 6F");
			return "[No winner]";
		}
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Paper)
		{
			system("color 4F");
			cout << "\a";
			return "[Computer]";
		}
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Scissors)
		{
			system("color 2F");
			return "[Player]";
		}
	}

	if (RockPaperScissors(PlayerChoice) == enRockPaperScissors::Paper)
	{
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Rock)
		{
			system("color 2F");
			return "[Player]";
		}
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Paper)
		{
			system("color 6F");
		return "[No winner]";
		}
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Scissors)
		{
			system("color 4F");
			cout << "\a";
			return "[Computer]";
		}
	}

	if (RockPaperScissors(PlayerChoice) == enRockPaperScissors::Scissors)
	{
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Rock)
		{
			system("color 4F");
			cout << "\a";
			return "[Computer]";
		}
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Paper)
		{
			system("color 2F");
			return "[Player]";
		}
		if (RockPaperScissors(ComputerChoice) == enRockPaperScissors::Scissors)
		{
			system("color 6F");
			return "[No winner]";
		}
	}

}

void Game(int Rounds)
{
	int PlayerWins = 0;
	int ComputerWins = 0;
	int Draws = 0;

	for (int i = 1; i <= Rounds; i++)
	{
		cout << "\nRound [" << i << "] begins: \n";

		int PlayerChoice = UserChoice();
		int ComputerChoice = RandomNumber(1, 3);

		string Winner = RoundWinner(PlayerChoice, ComputerChoice);

		cout << "\n_____________________";
		cout << " Round [" << i << "] ";
		cout << "____________________\n";

		cout << "Player1 choice : ";
		cout << GetChoiceName(RockPaperScissors(PlayerChoice)) << endl;

		cout << "Computer choice: ";
		cout << GetChoiceName(RockPaperScissors(ComputerChoice)) << endl;

		cout << "Round winner   : ";
		cout << Winner << endl;

		cout << "____________________________________________________\n";

		if (Winner == "[Player]")
		{
			PlayerWins++;
		}

		if (Winner == "[Computer]")
		{
			ComputerWins++;
		}

		if (Winner == "[No winner]")
		{
			Draws++;
		}
	}

	string FinalWinner = "";

	int Max = MaxNumber(Draws, PlayerWins, ComputerWins);

	if (Max == PlayerWins)
	{
		system("color 2F");
		FinalWinner = "Player";
	}
	else if (Max == ComputerWins)
	{
		system("color 4F");
		cout << "\a";
		FinalWinner = "Computer";
	}
	else
	{
		system("color 6F");
		FinalWinner = "No winner";
	}

	cout << "\n\n\t\t\t___________________________________________________________\n\n";
	cout << "\t\t\t\t\t+++ G a m e O v e r +++";
	cout << "\n\t\t\t___________________________________________________________\n\n";

	cout << "\n\t\t\t___________________  [Game Results]  ______________________\n\n";

	cout << "\t\t\tGame Rounds	   : " << Rounds << endl;
	cout << "\t\t\tPlayer1 won times  : " << PlayerWins << endl;
	cout << "\t\t\tComputer won times : " << ComputerWins << endl;
	cout << "\t\t\tDraw times	   : " << Draws << endl;
	cout << "\t\t\tFinal Winner	   : " << FinalWinner << endl;

	cout << "\t\t\t___________________________________________________________\n";

}

bool ClearScreen(char PlayAgain)
{
	return (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	Game(HowManyRounds());

	char PlayAgain;
	cout << "\t\t\t\nDo you want to play again? Y/N? ";
	cin >> PlayAgain;

	while (ClearScreen(PlayAgain))
	{
		system("cls");
		Game(HowManyRounds());
		cout << "\t\t\t\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;

	}
	cout << endl;

	return 0;
}