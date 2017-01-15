#include <iostream>
#include <string>
#include "FBullCowGame.h"

using namespace std;

FBullCowGame BCGame; // maak BCGame aan van de class FBullCowGame

void PrintIntro();
string GetGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();

		PlayGame();

		PrintGameSummary();

		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain); // doet dit iedere keer opnieuw zolang de speler het spel opnieuw wil spelen

	return 0;
}


void PrintIntro() // intro van game scherm
{
	cout << "\nHallo en welcome bij Bulls en Cows, een leuke word game." << endl;
	cout << "          }   {         ___ " << endl;
	cout << "          (o o)        (o o) " << endl;
	cout << "   /-------\\ /          \\ /-------\\ " << endl;
	cout << "  / | BULL |O            O| COW  | \\ " << endl;
	cout << " *  |-,--- |              |------|  * " << endl;
	cout << "    ^      ^              ^      ^ " <<endl;
	cout << "\nKan jij de " << BCGame.GetHiddenWordLength() << " letters raden waar ik aan denk." << endl;
	cout << "Je krijgt " << BCGame.GetMaxTries() << " beurten om het te raden \n" << endl;
}

string GetGuess() // voerd de speler zijn antwoord in
{
	EWordStatus Status;
	string guess = "";

	do
	{
		int Guess = BCGame.GetCurrentTry(); // krijg de de spelers zij beurt
		cout << Guess << ": ";

		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess); // krijgt de status van het woord

		switch (Status) // checkt wat de status van het woord is
		{
		case EWordStatus::Wrong_Length:
			cout << "Vul een " << BCGame.GetHiddenWordLength() << " letter woord in:" << endl;
			break;

		case EWordStatus::Not_Lowercase:
			cout << "Vul het woord zonder hoofdletters in:" << endl;
			break;

		case EWordStatus::Not_isogram:
			cout << "Vul iedere letter maar 1 keer in:" << endl;
			break;

		default:
			return guess;
			break;
		}
	} while (Status != EWordStatus::OK); // doet dit iedere keer opnieuw als de speler een ongeldig woord heeft ingevoerd
}


void PlayGame()
{
	BCGame.Reset(); // reset de game
	int MaxTries = BCGame.GetMaxTries(); // krijgt het aantal maximaale beurten

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) // blijft het iedere keer opneiuw doen tot de speler heeft gewonnen of het aantal beurten op is
	{
		string guess = GetGuess();

		FBullCowCount BullCowCount = BCGame.SubmitGuess(guess); // submit het antwoord van de gast

		cout << "Bulls = " << BullCowCount.Bulls;
		cout << ". Cows = " << BullCowCount.Cows << "\n" << endl;
	}

	return;
}

bool AskToPlayAgain() // vraag of de speler het opnieuw wil spelen
{
	string vraag;
	cout << "Wil je het nog een keer doen ja/nee ";
	cin >> vraag;
	cout << endl;

	if (vraag == "ja" || vraag == "Ja")
	{
		return true;
	}

	else
	{
		return false;
	}
}

void PrintGameSummary() // kijkt of je de game heb gewonnen of verloren 
{
	if (BCGame.IsGameWon()) // als de game gewonnen is
	{
		cout << "Gefeliciteerd je heb gewonnen" << endl;
	}

	else
	{
		cout << "Jammer je heb verloren" << endl;
	}
}


