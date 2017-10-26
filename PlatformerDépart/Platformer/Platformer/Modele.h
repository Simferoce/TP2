
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>


class Controle;

class Modele
{
public:
	friend Controle;
	enum PositonInformation { Nickname, Password, Prenom, Nom, Courriel, Pointages};
	enum ResultatAuthentification { Reussi, UtilisateurFormat, MotPassFormat, Echouer };
	enum StringId {};

	static sf::Font font;
	static Modele* GetInstance();
	static void Decharger();	
	/// <summary>
	/// Obtient le texte correspondant à l'identifiant
	/// </summary>
	/// <param name="id">Identifiant du texte.</param>
	/// <returns></returns>
	static std::string GetText(StringId id);
	/// <summary>
	/// Diviser une chaîne de caractère.
	/// </summary>
	/// <param name="stringASplit">La chaîne de caractère à diviser.</param>
	/// <param name="caractereQuiSplit">Le caractère qui sert pour la division.</param>
	/// <returns></returns>
	static std::vector<std::string> split(std::string strinASplit, char caractereQuiSplit);
	/// <summary>
	/// <Model> Authentifier l'utilisateur en vérifiant la correspondance entre l'utilisateur et le mot de passe entré.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur à vérifier.</param>
	/// <param name="motPass">Le mot de passe entré.</param>
	/// <param name="ligne">La ligne ou l'usager a été trouvée</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gardées</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier);
private:
	static Modele* instance;
	static std::string emplacementFont;
	static std::map<StringId, std::string> dictionnaire;
	Modele();
	Modele(const Modele&) = delete;
	void operator=(const Modele&) = delete;

};

