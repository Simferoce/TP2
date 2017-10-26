#include "Modele.h"
#include <fstream>
#include <vector>
#include <string>

Modele* Modele::instance = nullptr;
sf::Font Modele::font;

Modele::Modele()
{
}
//A TESTER
std::vector<std::string> Modele::split(std::string strinASplit, char caractereQuiSplit)
{
	std::vector<std::string> stringSplit;
	int i = 0;
	std::string currentString = "";
	while(i < strinASplit.length())
	{

		if (strinASplit[i] == caractereQuiSplit)
		{
			stringSplit.push_back(currentString);
			currentString = "";
		}
		else
		{
			currentString += strinASplit[i];
		}
		i++;
	}
	stringSplit.push_back(currentString);
	return stringSplit;
}

Modele * Modele::GetInstance()
{
	if (instance == nullptr)
		instance = new Modele();
	return instance;
}

void Modele::Decharger()
{
	delete instance;
	instance = nullptr;
}

Modele::ResultatAuthentification Modele::AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier)
{
	int ligneCourrante = 0;
	std::ifstream readFile(emplacementFichier, std::ios::out | std::ios::app);
	std::string line = "";
	if(readFile.is_open())
	{
		while(std::getline(readFile,line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			if (stringSplit[Nickname] == utilisateur && stringSplit[Password] == motPass)
			{
				ligne = ligneCourrante;
				return Modele::ResultatAuthentification::Reussi;
			}
			ligneCourrante++;
		}
	}
	ligne = 0;
	return Modele::ResultatAuthentification::Echouer;
}
sf::Text Modele::CreateTextLine(std::string text, float posX, float posY)
{
	sf::Text textLine;
	textLine.setFont(font);
	textLine.setString(text);
	textLine.setCharacterSize(24);
	textLine.setColor(sf::Color::White);
	textLine.setStyle(sf::Text::Bold);
	textLine.setPosition(posX, posY);
	return textLine;
}
bool Modele::InitFont(std::string chemin)
{
	if (!Modele::font.loadFromFile(chemin))
	{
		return false;
	}
	return true;
}
