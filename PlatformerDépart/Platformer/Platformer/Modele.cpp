#include "Modele.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Scene.h"

Modele* Modele::instance = nullptr;
/// <summary>
/// The users{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
std::list<User> Modele::users;
std::map<Modele::StringId, std::string> Modele::dictionnaire = { 
	std::pair<StringId,std::string>
	(SceneTitreMenuPrincipale,"Enter:Valider|1:Gestion de Compte|2:Meilleurs Scores")
	, std::pair<StringId,std::string>
	(PointageJeu,"Pointage: ")
};
sf::Font Modele::font = sf::Font();
std::string Modele::emplacementFont = "Ressources\\Fonts\\Peric.ttf";
const sf::Color Modele::TEXTE_COULEUR = sf::Color::White;
std::string Modele::sauvegardeEmplacement = "userpass.txt";
std::string Modele::emplacementFond = "Ressources\\Sprites\\Title.png";
sf::Texture Modele::textureFond = sf::Texture();
sf::Texture* Modele::textureMur[NBRE_TEXTURE_MUR] = { new Texture(), new Texture(),new Texture(), new Texture(),new Texture(), new Texture(),new Texture() };
std::string Modele::emplacementTextureMurPrefixe = "Ressources\\Tiles\\BlockA";
std::string Modele::emplacementTextureMurSuffixe = ".png";
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

bool Modele::Init(std::string emplacement)
{
	std::ifstream readFile(emplacement, std::ios::out | std::ios::app);
	std::string line = "";
	while(std::getline(readFile,line))
	{
		users.push_back(User(line));
	}
	if (!Modele::font.loadFromFile(emplacementFont))
		return false;
	if (!Modele::textureFond.loadFromFile(emplacementFond))
		return false;
	for(int i =0; i < NBRE_TEXTURE_MUR; ++i)
		if(!textureMur[i]->loadFromFile(emplacementTextureMurPrefixe + std::to_string(i) + emplacementTextureMurSuffixe))
			return false;
	return true;
}

void Modele::Decharger()
{
	for(int i = 0; i < NBRE_TEXTURE_MUR; ++i)
	{
		delete textureMur[i];
		textureMur[i] = nullptr;
	}
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
	if(topScore.size() > 10)
		topScore.resize(10);
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
	if (topScore.size() > 10)
		topScore.resize(10);
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
				if (std::stoi(*iter) == score)
				{
					topScore.push_back(TopScore(std::stoi(*iter), stringSplit[Nickname]));
				}
			}
		}
	}
	std::sort(topScore.begin(), topScore.end());
	std::reverse(topScore.begin(), topScore.end());
	if (topScore.size() > 10)
		topScore.resize(10);
	return topScore;
}
std::vector<Modele::TopScore> Modele::GetTopTenResult(std::string emplacementSauvegarde)
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
	if (topScore.size() > 10)
		topScore.resize(10);
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
	if (UserExist(utilisateur, GetSaveEmplacement(), ligne))
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
bool Modele::VerifierCourriel(std::string courriel)
{
	int nbFoisArobas = 0;
	int positionArobas = 0;
	int dernierePositionPoint = 0;
	if((courriel[courriel.size()-1]=='m' && courriel[courriel.size() - 2] == 'o' && courriel[courriel.size() - 3] == 'c' && courriel[courriel.size() - 4] == '.' && courriel[courriel.size() - 5] != '@')
		|| ((courriel[courriel.size() - 1] == 'a') && (courriel[courriel.size() - 2] == 'c') && (courriel[courriel.size() - 3] == '.') && (courriel[courriel.size() - 4] != '@')))
	{
		
	}
	else
	{
		return false;
	}
	for (int i = 0; i<courriel.size(); i++)
	{
		if (courriel[i] == '@')
		{
			nbFoisArobas++;
			positionArobas = i;
		}
		else if (courriel[i] == '.')
		{
			dernierePositionPoint = i;
		}
		else if ((courriel[i]<'a' || courriel[i]>'z') && (courriel[i]<'A' || courriel[i]>'Z') && courriel[i] != '_' && courriel[i] != '-')
		{
			return false;
		}
	}
	if (nbFoisArobas != 1 || positionArobas>dernierePositionPoint)
	{
		return false;
	}
	return true;
}

void Modele::Save(std::string emplacement)
{
	std::ofstream stream = std::ofstream(emplacement, std::ios::in);
	for each(User user in users)
	{
		std::string stringToWrite = user.nickname + ":" + user.password + ":" + user.prenom + ":" + user.nom + ":" + user.courriel + ":";
		auto size = user.meilleurPointages.size();
		int i = 0;
		for(auto iter = user.meilleurPointages.begin(); iter != user.meilleurPointages.end(); ++iter)
		{
			stringToWrite += std::to_string(*iter);
			if (i != size - 1)
				stringToWrite += ",";
			++i;
		}
		stringToWrite += "\n";
		stream << stringToWrite;
	}
}

void Modele::Clear()
{
	users.clear();
}
bool Modele::AjouterScore(std::string user, int score, std::string emplacement)
{
	for(auto iter = users.begin(); iter != users.end(); ++iter)
	{
		if(iter->nickname == user)
		{
			iter->meilleurPointages.push_back(score);
			return true;
		}
	}
	return false;
}
bool Modele::AjouterCompte(std::string infos)
{
	std::fstream readFile(GetSaveEmplacement(),std::ios::in | std::ios::out | std::ios::app);
	if (readFile.is_open())
	{
		readFile << infos << std::endl;
	}
	else
	{
		return false;
	}
	readFile.close();
	return true;
}
std::vector<std::string> Modele::GetUserInfo(std::string user)
{
	std::ifstream readFile(GetSaveEmplacement(), std::ios::out | std::ios::app);
	std::string line = "";
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			if (stringSplit[Nickname] == user)
			{
				return stringSplit;
			}
		}
	}
}
bool Modele::ChangeInfoUser(std::string info, std::string user)
{
	//code problématique pour le moment

	/*std::ifstream readFile(GetSaveEmplacement(), std::ios::out | std::ios::app);
	std::ofstream writeFile("userPass.txt", std::ios::in | std::ios::app);
	std::string line = "";
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			std::vector<std::string> stringSplit = split(line, ':');
			if (stringSplit[Nickname] == user)
			{
				writeFile << info << std::endl;
			}
			else
			{
				writeFile << line << std::endl;
			}
		}
	}
	readFile.close();
	writeFile.close();*/
	return true;
}


