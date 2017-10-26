#include "Modele.h"
#include <fstream>
#include <vector>
#include <string>

Modele* Modele::instance = nullptr;
std::map<Modele::StringId, std::string> Modele::dictionnaire = {};
sf::Font Modele::font = sf::Font();
std::string Modele::emplacementFont = "Ressources\\Fonts\\Peric.ttf";
const sf::Color Modele::TEXTE_COULEUR = sf::Color::White;
std::string Modele::sauvegardeEmplacement = "userpass.txt";
std::string Modele::emplacementFond = "Ressources\\Sprites\\Title.png";
sf::Texture Modele::textureFond = sf::Texture();
Modele::Modele()
{

}
std::vector<std::string> Modele::split(std::string stringASplit, char caractereQuiSplit)
{
	std::vector<std::string> stringSplit;
	int i = 0;
	std::string currentString = "";
	while(i < stringASplit.length())
	{

		if (stringASplit[i] == caractereQuiSplit)
		{
			stringSplit.push_back(currentString);
			currentString = "";
		}
		else
		{
			currentString += stringASplit[i];
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

bool Modele::Init()
{
	if (!Modele::font.loadFromFile(emplacementFont))
		return false;
	if (!Modele::textureFond.loadFromFile(emplacementFond))
		return false;
	return true;
}

void Modele::Decharger()
{
	delete instance;
	instance = nullptr;
}

std::string Modele::GetText(StringId id)
{
	return dictionnaire[id];
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
const sf::Font & Modele::GetFont()
{
	return font;
}
const std::string & Modele::GetSaveEmplacement()
{
	return sauvegardeEmplacement;
}
const sf::Texture & Modele::GetTextureBackground()
{
	return textureFond;
}
sf::Text Modele::CreateTextLine(std::string text, float posX, float posY)
{
	sf::Text textLine;
	textLine.setFont(font);
	textLine.setString(text);
	textLine.setCharacterSize(24);
	textLine.setFillColor(sf::Color::White);
	textLine.setStyle(sf::Text::Bold);
	textLine.setPosition(posX, posY);
	return textLine;
}
