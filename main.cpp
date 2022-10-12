#include <iostream>
#include <random>

namespace Random
{
	std::random_device rd;
	//unsigned int clock{ static_cast<unsigned int>(
	//	std::chrono::steady_clock::now().time_since_epoch().count()) };
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };

	int uniform32(int min, int max)
	{
		std::uniform_int_distribution x{ min, max };
		return x(mt);
	}

	unsigned int get32()
	{
		return mt();
	}
}

namespace Constants
{
	inline constexpr int guesses{ 7 };
}

int parseInput(int guessNumber)
{
	while (true)
	{
		std::cout << "Guess #" << guessNumber << ": ";
		int x{};
		std::cin >> x;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Incorrect input. Please try again.\n";
		}
		else
		{
			if (x < 1 || x > 100)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Incorrect input. Please try again.\n";
				continue;
			}

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return x;
		}
	}
}

bool playAgain()
{
	while (true)
	{
		std::cout << "Do you want to play again? (y/n): ";
		char x{};
		std::cin >> x;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch(x)
		{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			std::cerr << "Invalid input. Please try again.\n";
		}
	}
}

int main()
{
	while (true)
	{

		std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.\n";

		const int randomNumber{ Random::uniform32(1, 100) };

		for(int i { 1 }; i <= Constants::guesses; ++i)
		{
			int x{ parseInput(i) };
			if (x < randomNumber)
			{
				std::cout << "Your guess is too low.\n";
			}
			else if (x > randomNumber)
			{
				std::cout << "Your guess is too high.\n";
			}
			else
			{
				std::cout << "Correct! You win!\n";
				break;
			}
			if (i % Constants::guesses == 0) std::cout << 
				"Sorry, you lose. The correct number was " << randomNumber << ".\n";
		}
		bool cont{ playAgain() };
		if (cont == false) break;
	}

	std::cout << "Thanks for playing!";

	return 0;
}