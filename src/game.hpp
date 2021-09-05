#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <stdlib.h>

enum {START, PLAY, QUIT};
enum {ENGLISH, FRENCH, SPANISH};

class Game
{
public:
	Game();
	void inGame();
	bool start();
	bool startLanguage();
	void writeInput();
	unsigned int end(const std::string endText);
	bool inputIsTrue(std::string inputChoice) const;
	bool reset(const std::string m);
	void clearConsole() const;
	void generation();
	void draw() const;
	bool verifQuit() const;
private:
	unsigned int m_state, m_life, m_letterFind;
	unsigned int m_language; //0 = english, 1 = french (francais)
	std::string m_input, m_secretWord, m_differentLetter, m_secretWordWithoutAccent, m_secretWordHide;

};

#endif