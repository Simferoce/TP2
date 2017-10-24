#include "Modele.h"
#include <fstream>
#include <vector>

Modele* Modele::instance = nullptr;

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

Modele::ResultatAuthentification Modele::AuthentifierUtilisateur(std::string utilisateur, std::string motPass)
{
	{
		std::ifstream readFile("userpass.txt", std::ios::out | std::ios::app);
		std::string line = "";
		if(readFile.is_open())
		{
			while(std::getline(readFile,line))
			{
				std::vector<std::string> stringSplit = split(line, ':');
				if (stringSplit[Nickname] == utilisateur && stringSplit[Password] == motPass)
					return Modele::ResultatAuthentification::Reussi;
			}
		}

	}

	return Modele::ResultatAuthentification::Echouer;
}
