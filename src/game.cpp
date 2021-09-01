#include "game.hpp"

Game::Game() : m_life(11), m_state(START), m_language(1), m_input("")
{

}

void Game::inGame()
{
	start();
}

void Game::start()
{
	std::cout << "Hangman by Skalefou\n\nPlease choose a language :\n1 - English UK\n2 - French (Français) " << std::endl;
	bool a {true};
	while (a)
	{
		writeInput();
		if (inputIsTrue("english,french,français,anglais,francais,uk,1,2,"))
			a = false; 
	}
	if (m_input == "french" || "francais" || "français" || "2")
		m_language = 0;
}

void Game::writeInput()
{
	while (!(std::cin >> m_input))
	{
		std::cout << "Error: Please re-enter your choice." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::transform(m_input.begin(), m_input.end(), m_input.begin(), (int (*)(int))std::tolower);
}

bool Game::inputIsTrue(std::string inputChoice)
{
	std::string a {""};
	bool b {false};
	for (unsigned int i = 0; i < std::size(inputChoice); i++)
	{
		if (inputChoice[i] == ',')
		{
			if (m_input == a)
			{
				b = true;
				break;
			}
			a.clear();
		}
		else
			a += inputChoice[i];
	}
	return b;
}
