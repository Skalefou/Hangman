#include "dictionary.hpp"
#include <fstream>
#include <cctype>
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;

std::string Dictionary::loadWord(const unsigned int language)
{
	const std::string frenchList{ "voiture,maison,maman,vivre,griffe,chaton,h�licopt�re,constitution,a�roplane,ornithorynque,anxi�t�,photosynth�se,arbre,tibia,ventre,train,montpellier,marseille,lille,paris,bordeaux,strasbourg,tour,france,europe,am�rique,espagne,angleterre,russie,ordinateur,math�matiques,sport,robotique,trajectoire,gazelle,litt�rature,philosophie,philanthrope,espoir,nihilisme,musique,artiste,barrage,vieillard,jeunesse,natation,horizon,point,grandiloquent,traducteur,outrage," };
	const std::string englishList{ "car,home,mother,live,claw,kitten,helicopter,constitution,airplane,platypus,anxiety,photosynthesis,tree,tibia,stomach,train,london,birmingham,liverpool,manchester,scotland,glasgow,bristol,france,europe,america,spain,england,russia,computer,mathematics,sport,robotic,trajectory,gazelle,literature,philosophy,philanthropist,hope,nihilism,music,artist,roadblock,ancestor,youthfulness,swimming,horizon,point,bombastic,translator,indignity" };
	const std::string spanishList{ "carro,casa,madre,viver,garra,gatito,helic�ptero,constituci�n,avi�n,ornitorrinco,ansiedad,fotos�ntesis,�rbol,tibia,est�mago,tren,madrid,barcelona,valencia,m�laga,bilbao,zaragoza,andaluc�a,francia,europa,america,espa�a,inglaterra,rusia,computadora,matem�ticas,deporte,rob�tica,sendero,gacela,literatura,filosof�a,fil�ntropo,esperar,nihilismo,m�sica,artista,bombardeo,anciano,juventud,nadando,horizonte,punto,grandilocuente,traductor,indignacion," };
	if (language == FRENCH)
		return giveWord(frenchList);
	else if (language == SPANISH)
		return giveWord(spanishList);
	else
		return giveWord(englishList);
}

std::string Dictionary::differentLetter(const std::string word)
{
	std::string differentLetterWord =  "";
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if (differentLetterWord.length() > 0)
		{
			bool a{ false };
			for (unsigned int y = 0; y < differentLetterWord.length(); y++)
				if (differentLetterWord[y] == word[i])
					a = true;
			if(!a)
				differentLetterWord += word[i];
		}
		else
			differentLetterWord += word[i];
	}
	return differentLetterWord;
}

std::string Dictionary::removeAccentWord(std::string word)
{
	std::string w { "" };
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if (word[i] == '�' or word[i] == '�')
			w += 'e';
		else if (word[i] == '�')
			w += 'i';
		else if (word[i] == '�')
			w += 'o';
		else if (word[i] == '�')
			w += 'u';
		else if (word[i] == '�')
			w += 'a';
		else if (word[i] == '�')
			w += 'n';
		else
			w += word[i];
	}
	return w;
}

unsigned int Dictionary::randomNumber(const unsigned int countLine)
{
	std::random_device os_seed;
	const u32 seed = os_seed();
	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, countLine);
	return distribute(generator);
}

std::string Dictionary::giveWord(const std::string &str)
{
	unsigned int count {0};
	for (unsigned int i = 0; i < str.length(); i++)
		if (str[i] == ',')
			count++;
	unsigned int number = randomNumber(count);
	std::string word{ "" };
	count = 0;
	for (unsigned int i = 0; i <= str.length(); i++)
	{
		if (str[i] == ',')
			count++;
		else if (count == number)
		{
			word += str[i];
		}
	}
	return word;
}