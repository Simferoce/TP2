
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
	friend Controle;
	static sf::Font font;
	static std::string sauvegardeEmplacement;
	static std::string emplacementFond;
	static sf::Texture textureFond;
public:
	enum PositonInformation { Nickname, Password, Prenom, Nom, Courriel, Pointages};
	enum ResultatAuthentification { Reussi, UtilisateurFormat, MotPassFormat, Echouer };
	enum StringId {};
	static const int GROSSEUR_CARACTERE = 24;
	static const sf::Text::Style TEXTE_STYLE = sf::Text::Style::Bold;
	static const sf::Color TEXTE_COULEUR;
	static sf::Text CreateTextLine(std::string text, float posX, float posY);
	static Modele* GetInstance();	
	/// <summary>
	/// Initialise l'instance.
	/// </summary>
	static bool Init();	
	/// <summary>
	/// Decharger l'instance.
	/// </summary>
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
	/// <summary>
	/// Obtien la police d'ecriture de base du mod�le.
	/// </summary>
	/// <returns>La police d'�criture de base du mod�le.</returns>
	static const sf::Font& GetFont();
	static const std::string& GetSaveEmplacement();
	static const sf::Texture& GetTextureBackground();
private:
	static Modele* instance;
	static std::string emplacementFont;
	static std::map<StringId, std::string> dictionnaire;
	Modele();
	Modele(const Modele&) = delete;
	void operator=(const Modele&) = delete;

};

