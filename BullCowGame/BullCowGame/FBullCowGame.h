#pragma once
#include <iostream>
#include <string>

struct FBullCowCount // maak een struct bulcow count 
{
	int Bulls = 0;
	int  Cows = 0;
};

enum class EWordStatus // maak een enum woord status aan
{
	OK,
	Not_isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
	public:
		FBullCowGame();

		void Reset(); 

		int GetMaxTries();
		int GetCurrentTry();
		int GetHiddenWordLength();

		bool IsGameWon() const;

		EWordStatus CheckGuessValidity(std::string);
		FBullCowCount SubmitGuess(std::string);

	private:
		int MyCurrentTry;
		int MyMaxTries;

		bool bWon;

		bool IsIsogram(std::string guess);
		bool Islower(std::string guess);

		std::string MyHiddenWord;
};


