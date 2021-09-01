#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#if defined(WIN32) && !defined(UNIX)
#include <stdlib.h>
#endif

enum {START, PLAY, GAME_OVER, QUIT};

class Game
{
public:
	Game();
	void inGame();
	void start();
	void writeInput();
	bool inputIsTrue(std::string inputChoice);
private:
	unsigned int m_state, m_life;
	unsigned int m_language; //0 = french (francais), 1 = english
	std::string m_input;
};

#endif