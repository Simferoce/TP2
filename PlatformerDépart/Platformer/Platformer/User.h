#pragma once
#include <string>
#include <list>

class User
{
public:
	std::string nickname;
	std::string password;
	std::string nom;
	std::string prenom;
	std::string courriel;
	std::list<int> meilleurPointages;
	User(std::string ligneUser);
	~User();
};

