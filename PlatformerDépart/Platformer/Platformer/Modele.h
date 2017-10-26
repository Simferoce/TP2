#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <string>

class Modele
{
	enum PositonInformation { Nickname, Password, Prenom, Nom, Courriel, Pointages};
	static Modele* instance;
	Modele();
	Modele(const Modele&) = delete;
	void operator=(const Modele&) = delete;
public:
	static bool InitFont(std::string chemin);
	static sf::Font font;
	static sf::Text CreateTextLine(std::string text, float posX, float posY);
	static std::vector<std::string> split(std::string strinASplit, char caractereQuiSplit);
	static Modele* GetInstance();
	static void Decharger();
	enum ResultatAuthentification { Reussi, UtilisateurFormat, MotPassFormat, Echouer };
	/// <summary>
	/// <Model> Authentifier l'utilisateur en vérifiant la correspondance entre l'utilisateur et le mot de passe entré.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur à vérifier.</param>
	/// <param name="motPass">Le mot de passe entré.</param>
	/// <param name="ligne">La ligne ou l'usager a été trouvée</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gardées</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier);
};

