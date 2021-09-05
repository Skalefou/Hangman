#include "game.hpp"
#include "dictionary.hpp"

static const std::string drawWant[3]{ {"Please enter a letter:"}, {"Veuillez entrer une lettre :"}, {"Por favor ingrese una letra:"}};
static const std::string endWin[3]{ {"Congratulations! You win!"}, {"Félicitation ! Vous avez gagné !"}, {"¡Felicitaciones!Has ganado!"}};
static const std::string endGameOver[3]{ {"Too bad you lost! Here is the word: "}, {"Dommage, vous avez perdu ! Voici le mot : "}, {"¡Lástima que hayas perdido! Aquí está la palabra:"}};
static const std::string endPurpose[3]{ {"\n1 - Retry\n2 - Change the language\n3 - Quit"},{"\n1 - Recommencer\n2 - Changer la langue\n3 - Quitter"},{"\n1 - Reiniciar\n2 - Cambiar el idioma\n3 - Dejar"}};

Game::Game() : m_life(11), m_state(START), m_language(ENGLISH), m_input(""), m_letterFind(0), m_differentLetter(""), m_secretWordHide("")
{}

void Game::inGame()
{
	bool quit = start();
	if (!quit)
	{
		generation();
		while (!quit)
		{
			clearConsole();
			draw();
			writeInput();

			if (verifQuit())
				quit = true;
			else if (m_input.length() == 1)
			{
				bool l = false;
				for (unsigned int i = 0; i < m_secretWordWithoutAccent.length(); i++)
				{
					if (m_input[0] == m_secretWordWithoutAccent[i])
					{
						m_secretWordHide[i] = m_secretWord[i];
						m_letterFind++;
						l = true;
					}
				}
				if (!l)
					m_life--;
			}
			if (m_letterFind == m_secretWordWithoutAccent.length())
				quit = reset(endWin[m_language]);
			else if (m_life == 0)
				quit = reset(endGameOver[m_language] + m_secretWord);
			
		}
	}
}

bool Game::start()
{
	bool quit {false}, chooseLanguage {false};
	do
	{
		chooseLanguage = false;
		quit = startLanguage();
		if (quit)
			break;
		std::string text{ "" };
		switch (m_language)
		{
		case ENGLISH:
			text = "Hangman by Skalefou\n\nPlease enter what you want to do :\n1 - Play\n2- Language\n3 - Quit\n";
			break;
		case FRENCH:
			text = "Pendu par Skalefou\n\nS'il vous plaît, veuillez entrer ce que vous voulez faire :\n1 - Jouer\n2 - Langue\n3 - Quitter\n";
			break;
		case SPANISH:
			text = "Ahorcado de Skalefou\n\nPor favor ingrese lo que desea hacer:\n1 - Jugar\n2 - Lengua\n3 - Dejar\n";
			break;
		}
		std::cout << text;
		bool a{ false };
		do
		{
			a = false;
			writeInput();
			if (!(inputIsTrue("play,language,quit,jouer,langue,quitter,jugar,lengua,dejar,1,2,3,")))
				a = true;
			else if (verifQuit() or m_input == "3")
			{
				quit = true;
				break;
			}
			else if (m_input == "play" or m_input == "jouer" or m_input == "jugar" or m_input == "1")
				a = false;
			else if (m_input == "language" or m_input == "langage" or m_input == "lengua" or m_input == "2")
				chooseLanguage = true;
			else
				a = true;
			
		} while (a);
		clearConsole();
		if (quit)
			break;
	} while (chooseLanguage);

	return quit;
}

bool Game::startLanguage()
{
	bool a{ false };
	do
	{
		a = false;
		std::cout << "Hangman by Skalefou\n\nPlease choose a language :\n1 - English UK\n2 - French (Français)\n3 - Spanish (Español)\n" << std::endl;
		writeInput();
		if (!(inputIsTrue("english,french,français,anglais,francais,uk,1,2,3,spanish,español,espagnol,francesa,ingles,espanol,quit,exit,")))
			a = true;
		else if (verifQuit())
			return true;
		else if (m_input == "english" or m_input == "anglais" or m_input == "uk" or m_input == "1" or m_input == "ingles")
			m_language = ENGLISH;
		else if (m_input == "french" or m_input == "francais" or m_input == "français" or m_input == "francesa" or m_input == "2")
			m_language = FRENCH;
		else if (m_input == "spanish" or m_input == "espagnol" or m_input == "español" or m_input == "espanol" or m_input == "3")
			m_language = SPANISH;
		else
			a = true;
		clearConsole();
	} while (a);
	return false;
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
	m_input = Dictionary::removeAccentWord(m_input);
}

unsigned int  Game::end(const std::string endText)
{
	while (true)
	{
		clearConsole();
		std::cout << endText << std::endl << endPurpose[m_language] << std::endl;
		writeInput();
		unsigned int a = 0;
		if (m_input.length() >= 3)
			for (unsigned int i = 0; i < m_input.length(); i++)
				if (m_input[i] == "cha"[i] or m_input[i] == "cam"[i])
					a++;
		if (verifQuit() or m_input == "3")
			return QUIT;
		else if (m_input == "retry" or m_input == "recommencer" or m_input == "reiniciar" or m_input == "1")
			return PLAY;
		else if (a == 3 or m_input == "2" or m_input == "language" or m_input == "idoma" or m_input == "langue")
			return START;
	} 	
}

bool Game::inputIsTrue(std::string inputChoice) const
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

bool Game::reset(const std::string m)
{
	m_life = 11;
	m_letterFind = 0;
	int a = end(m);
	if (a != QUIT)
	{
		clearConsole();
		if (a == START)
			start();
		generation();
		return false;
	}
	else
		return true;

}

void Game::clearConsole() const
{
#if defined(WIN32)
	system("cls");
#elif defined(UNIX)
	system("clear");
#endif
}

void Game::generation()
{
	m_secretWord = Dictionary::loadWord(m_language);
	m_differentLetter = Dictionary::differentLetter(m_secretWord);
	if (m_language != ENGLISH)
		m_secretWordWithoutAccent = Dictionary::removeAccentWord(m_secretWord);
	else
		m_secretWordWithoutAccent = m_secretWord;
	m_secretWordHide.resize(m_secretWordWithoutAccent.length(), '_');
}

bool Game::verifQuit() const
{
	return (m_input == "quit" or m_input == "exit" or m_input == "quitter" or m_input == "dejar");
}

void Game::draw() const
{

	std::cout << "Live : " << m_life << "/11" << std::endl << m_secretWordHide << std::endl << drawWant[m_language] << std::endl;
}
