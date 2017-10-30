#include "Modele.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Scene.h"

Modele* Modele::instance = nullptr;
std::map<Modele::StringId, std::string> Modele::dictionnaire = { 
	std::pair<StringId,std::string>
	(SceneTitreMenuPrincipale,"Enter:Valider|1:Gestion de Compte|2:Meilleurs Scores")
};
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
	ligne = -1;
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
std::vector<Modele::TopScore> Modele::GetTopTenResult(std::string user, int score, std::string emplacementSauvegarde)
{
	std::vector<Modele::TopScore> topScore; 
	std::ifstream readFile(emplacementSauvegarde, std::ios::out | std::ios::app);
	std::string line = "";
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			if(stringSplit[Nickname] == user)
			{
				std::vector<std::string> scoreUser = split(stringSplit[Pointages], ',');
				for(auto iter = scoreUser.begin(); iter != scoreUser.end(); ++iter)
				{
					if(std::stoi(*iter) == score)
					{
						topScore.push_back(TopScore(score, user));
					}
				}
			}
		}
	}
	return topScore;
}

std::vector<Modele::TopScore> Modele::GetTopTenResult(std::string user, std::string emplacementSauvegarde)
{
	std::vector<Modele::TopScore> topScore;
	std::ifstream readFile(emplacementSauvegarde, std::ios::out | std::ios::app);
	std::string line = "";
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			if (stringSplit[Nickname] == user)
			{
				std::vector<std::string> scoreUser = split(stringSplit[Pointages], ',');
				for (auto iter = scoreUser.begin(); iter != scoreUser.end(); ++iter)
				{
					topScore.push_back(TopScore(std::stoi(*iter), user));
				}
			}
		}
	}
	std::sort(topScore.begin(), topScore.end());
	std::reverse(topScore.begin(), topScore.end());
	return topScore;
}

std::vector<Modele::TopScore> Modele::GetTopTenResult(int score, std::string emplacementSauvegarde)
{
	std::vector<Modele::TopScore> topScore;
	std::ifstream readFile(emplacementSauvegarde, std::ios::out | std::ios::app);
	std::string line = "";
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			std::vector<std::string> scoreUser = split(stringSplit[Pointages], ',');
			for (auto iter = scoreUser.begin(); iter != scoreUser.end(); ++iter)
			{
				topScore.push_back(TopScore(std::stoi(*iter), stringSplit[Nickname]));
			}
		}
	}
	std::sort(topScore.begin(), topScore.end());
	std::reverse(topScore.begin(), topScore.end());
	return topScore;
}

bool Modele::UserExist(std::string user, std::string emplacementFichier, int& ligne)
{
	int ligneCourrante = 0;
	std::ifstream readFile(emplacementFichier, std::ios::out | std::ios::app);
	std::string line = "";
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			if (stringSplit[Nickname] == user)
			{
				ligne = ligneCourrante;
				return true;
			}
			ligneCourrante++;
		}
	}
	ligne = -1;
	return false;
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
bool Modele::VerifierUtilisateur(std::string utilisateur)
{
	if (utilisateur.size()<3 || utilisateur.size()>25)
	{
		return false;
	}
	int ligne = 0;
	if (Modele::UserExist(utilisateur, Modele::GetSaveEmplacement(), ligne))
	{
		return false;
	}
	return true;
}
bool Modele::VerifierMotDePasse(std::string motDePasse)
{
	if (motDePasse.size()<5 || motDePasse.size()>15)
	{
		return false;
	}
	int nbChiffres = 0;
	int nbCharSpecial = 0;
	int nbMajuscule = 0;
	int nbMinuscule = 0;
	for (int i = 0; i<motDePasse.size(); i++)
	{
		if (motDePasse[i] >= 'a' && motDePasse[i] <= 'z')
		{
			nbMinuscule++;
		}
		else if (motDePasse[i] >= 'A' && motDePasse[i] <= 'Z')
		{
			nbMajuscule++;
		}
		else if (motDePasse[i] >= '0' && motDePasse[i] <= '9')
		{
			nbChiffres++;
		}
		else
		{
			nbCharSpecial++;
		}
	}
	if (nbMinuscule<1 || nbMajuscule<1 || nbChiffres<1 || nbCharSpecial<1)
	{
		return false;
	}
	return true;
}
bool Modele::VerifierNom(std::string prenom)
{
	if (prenom.size()<2 || prenom.size()>25)
	{
		return false;
	}
	for (int i = 0; i<prenom.size(); i++)
	{
		if (prenom[i] != '-' && prenom[i] != '.' && (prenom[i]<'a' || prenom[i]>'z') && (prenom[i]<'A' || prenom[i]>'Z'))
		{
			return false;
		}
	}
	return true;
}
