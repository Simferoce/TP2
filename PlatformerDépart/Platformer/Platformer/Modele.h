#pragma once
#include <string>
#include <vector>

class Modele
{
	enum PositonInformation { Nickname, Password, Prenom, Nom, Courriel, Pointages};
	static Modele* instance;
	Modele();
	Modele(const Modele&) = delete;
	void operator=(const Modele&) = delete;
public:
	static std::vector<std::string> split(std::string strinASplit, char caractereQuiSplit);
	static Modele* GetInstance();
	static void Decharger();
	enum ResultatAuthentification { Reussi, UtilisateurFormat, MotPassFormat, Echouer };
	/// <summary>
	/// <Model> Authentifier l'utilisateur en v�rifiant la correspondance entre l'utilisateur et le mot de passe entr�.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur � v�rifier.</param>
	/// <param name="motPass">Le mot de passe entr�.</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass);
};

