
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics/Text.hpp>
#include <string>


class Controle;

class Modele
{
public:
	friend Controle;
	enum PositonInformation { Nickname, Password, Prenom, Nom, Courriel, Pointages};
private:
	enum ResultatAuthentification { Reussi, UtilisateurFormat, MotPassFormat, Echouer };
	enum StringId {};

	static sf::Font font;
	static bool InitFont(std::string chemin);
	static sf::Font font;
	static sf::Text CreateTextLine(std::string text, float posX, float posY);
	static Modele* GetInstance();
	static void Decharger();	
	/// <summary>
	/// Obtient le texte correspondant � l'identifiant
	/// </summary>
	/// <param name="id">Identifiant du texte.</param>
	/// <returns></returns>
	static std::string GetText(StringId id);
	/// <summary>
	/// Diviser une cha�ne de caract�re.
	/// </summary>
	/// <param name="stringASplit">La cha�ne de caract�re � diviser.</param>
	/// <param name="caractereQuiSplit">Le caract�re qui sert pour la division.</param>
	/// <returns></returns>
	static std::vector<std::string> split(std::string strinASplit, char caractereQuiSplit);
	/// <summary>
	/// <Model> Authentifier l'utilisateur en v�rifiant la correspondance entre l'utilisateur et le mot de passe entr�.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur � v�rifier.</param>
	/// <param name="motPass">Le mot de passe entr�.</param>
	/// <param name="ligne">La ligne ou l'usager a �t� trouv�e</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gard�es</param>
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

