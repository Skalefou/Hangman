#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#pragma once

#include "game.hpp"

class Dictionary
{
public:
	static std::string loadWord(const unsigned int language);
	static std::string differentLetter(const std::string word);
	static std::string removeAccentWord(std::string word);
private:
	static unsigned int randomNumber(const unsigned int countLine);
	static std::string giveWord(const std::string& str);
};

#endif
