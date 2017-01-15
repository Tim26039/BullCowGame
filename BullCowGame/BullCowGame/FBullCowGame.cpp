#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>

using namespace std;

FBullCowGame::FBullCowGame() // hier zeg je wat de class gelijk bij start moet doen
{
	FBullCowGame::Reset();
}

void FBullCowGame::Reset() // hier vul je de start waardes in
{
	const int MAX_TRIES = 10;
	MyMaxTries = MAX_TRIES;

	const string HIDDEN_WORD = "auto";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bWon = false;
	return;
}

int FBullCowGame::GetMaxTries() // hier return je het maximaal aantal kansen
{
	return  MyMaxTries;
}

int FBullCowGame::GetCurrentTry() // hier zeg je bij de hoeveelste kans je bent
{
	return MyCurrentTry;
}

int FBullCowGame::GetHiddenWordLength() // hier return je hoeveel letter het geheime word heeft
{
	int HiddenWordLength = MyHiddenWord.length();
	return HiddenWordLength;
}

bool FBullCowGame::IsGameWon() const // return je dat de speler gewonnen heeft
{
	return bWon;
}

EWordStatus FBullCowGame::CheckGuessValidity(string guess) // hier kijk je of wat speler heeft igevoerd kan 
{
	int HiddenWordLength = MyHiddenWord.length();

	if  (!IsIsogram(guess))
	{
		return EWordStatus::Not_isogram;
	}

	else if (!Islower(guess))
	{
		return EWordStatus::Not_Lowercase;
	}

	else if (guess.length() != HiddenWordLength)
	{
		return EWordStatus::Wrong_Length;
	}

	else
	{
		return  EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitGuess(string guess) // hier submit je het anwoord van de speler
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int HiddenWordLength = MyHiddenWord.length();

	for (int i = 0; i < HiddenWordLength; i++) // hier zeg je dat die dit iedere keer opnieuw moet tot het aantal van de woord lengte van het geheime woord
	{
		if (guess[i] == MyHiddenWord[i]) // hier zeg je als de letter op de juiste plek is in het word en geheim word dat bulls +1 is
		{
			BullCowCount.Bulls++;
		}

		else
		{
			for (int j = 0; j < HiddenWordLength; j++)  // hier doe je het zelfde als boven nog een keer alleen dan met een int j
			{
				if (guess[i] == MyHiddenWord[j]) // hier zeg je dat als de letter van het word dat je dacht in het geheime word zat maar niet op de juiste plek
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength) // als het geheime word goed is
	{
		bWon = true;
	}
		return BullCowCount;
}

bool FBullCowGame::IsIsogram(string guess) // hier kijk je of er geen dubbele letters in voor komen
{
	if (guess.length() <= 1)
	{
		return true;
	}

	map<char, bool> LetterSeen;

	for (auto letter : guess) // hier maak je een range based loop dat alle letter van guess in een char zet
	{
		letter = tolower(letter);

		if (LetterSeen[letter] == true) // als een letter al 1 keert voorkomt
		{
			return false;
		}

		else
		{
			LetterSeen[letter] = true ;
		}
	}
}

bool FBullCowGame::Islower(string guess) // hier kijk je of die alleen maar kleine letter heeft gebruikt
{
	for (auto letter : guess) // hier maak je een range based loop dat alle letter van guess in een char zet
	{
		if (!islower(letter)) // hier zeg je als het niet een kleine letter is 
		{
			return false;
		}
	}
}
