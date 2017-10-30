
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
public:
	struct TopScore
	{
		int score;
		std::string user;
		TopScore(int score, std::string user) : score(score), user(user){}
		bool operator<(const TopScore& other) { return score < other.score; };
	};
	enum PositonInformation { Nickname, Password, Prenom, Nom, Courriel, Pointages};
	enum ResultatAuthentification { Reussi, UtilisateurFormat, MotPassFormat, Echouer };
	enum StringId { SceneTitreMenuPrincipale };
	//Écriture style/couleur/police
	static const int GROSSEUR_CARACTERE = 24;
	static const sf::Text::Style TEXTE_STYLE = sf::Text::Style::Bold;
	static const sf::Color TEXTE_COULEUR;
	static const int MAX_NICKNAME_LENGTH = 25;
	static const int MIN_NICKNAME_LENGTH = 3;
	static const int MAX_PASSWORD_LENGTH = 15;
	static const int MIN_PASSWORD_LENGTH = 5;
	static sf::Text CreateTextLine(std::string text, float posX, float posY);
	static bool AjouterCompte(std::string infos);
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
	/// <param name="ligne">La ligne ou l'usager a été trouvée, -1 si pas trouver.</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gardées</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier);	
	/// <summary>
	/// Obtien la police d'ecriture de base du modèle.
	/// </summary>
	/// <returns>La police d'écriture de base du modèle.</returns>
	static const sf::Font& GetFont();	
	/// <summary>
	/// Obtient l'emplacement du fichier de sauvegarde.
	/// </summary>
	/// <returns>L'emplacement du fichier de sauvegarde.</returns>
	static const std::string& GetSaveEmplacement();	
	/// <summary>
	/// Obtient la texture du fond
	/// </summary>
	/// <returns>La texture du fond</returns>
	static const sf::Texture& GetTextureBackground();
	static std::vector<TopScore> GetTopTenResult(std::string user, int score, std::string emplacementSauvegarde);
	static std::vector<TopScore> GetTopTenResult(std::string user, std::string emplacementSauvegarde);
	static std::vector<TopScore> GetTopTenResult(int score, std::string emplacementSauvegarde);
	/// <summary>
	/// Détermine si l'utilisateur existe.
	/// </summary>
	/// <param name="user">L'utilisateur.</param>
	/// <param name="emplacementFichier">l'emplacement du fichier de sauvegarde.</param>
	/// <param name="ligne">La ligne trouver, -1 si pas trouver.</param>
	/// <returns></returns>
	static bool UserExist(std::string user, std::string emplacementFichier, int& ligne);	
	/// <summary>
	/// Verifier l'utilisateur.
	/// </summary>
	/// <param name="utilisateur">Utilisateur.</param>
	/// <returns></returns>Vrai si l'utilisateur est correct
	static bool VerifierUtilisateur(std::string utilisateur);
	/// <summary>
	/// Verifier le mot de passe.
	/// </summary>
	/// <param name="motDePasse">mot de passe</param>
	/// <returns></returns>Vrai si le mot de passe est correct
	static bool VerifierMotDePasse(std::string motDePasse);
	static bool VerifierNom(std::string prenom);
private:
	static Modele* instance;
	//Police de base
	static sf::Font font;
	//Police emplacement
	static std::string emplacementFont;
	//Emplacement du fichier de sauvegarde
	static std::string sauvegardeEmplacement;
	//Fond du menu principale
	static std::string emplacementFond;
	static sf::Texture textureFond;
	//Dictionnaire des chaînes de caractères
	static std::map<StringId, std::string> dictionnaire;
	Modele();
	Modele(const Modele&) = delete;
	void operator=(const Modele&) = delete;
};

