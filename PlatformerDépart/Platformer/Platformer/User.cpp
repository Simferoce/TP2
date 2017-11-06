#include "User.h"
#include <sstream>


User::User(std::string ligneUser)
{
	std::istringstream ss(ligneUser);

	std::getline(ss, nickname, ':');
	std::getline(ss, password, ':');
	std::getline(ss, prenom, ':');
	std::getline(ss, nom, ':');
	std::getline(ss, courriel, ':');
	std::string meilleurPointagesString;
	std::getline(ss, meilleurPointagesString, ':');

	std::istringstream ssPointages(meilleurPointagesString);
	std::string meilleurScore;
	while (std::getline(ssPointages, meilleurScore, ','))
		meilleurPointages.push_back(std::stoi(meilleurScore));
}

User::~User()
{
}
