#pragma once
#include <string>
#include "Modele.h"
#include "Scene.h"

class Controle
{
	static Controle* instance;
	Controle();
	Controle(const Controle&) = delete;
	void operator=(const Controle&) = delete;
public:	
	static void Decharger();
	static Controle* GetInstance();	
	/// <summary>
	/// Obtient le texte correspondant à l'identifiant
	/// </summary>
	/// <param name="id">Identifiant du texte.</param>
	/// <returns></returns>
	static std::string GetText(Modele::StringId id);
	/// <summary>
	/// Diviser une chaîne de caractère.
	/// </summary>
	/// <param name="stringASplit">La chaîne de caractère à diviser.</param>
	/// <param name="caractereQuiSplit">Le caractère qui sert pour la division.</param>
	/// <returns></returns>
	static std::vector<std::string> split(std::string stringASplit, char caractereQuiSplit);
	/// <summary>
	/// <Controleur> Authentifier l'utilisateur en vérifiant la correspondance entre l'utilisateur et le mot de passe entré.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur à vérifier.</param>
	/// <param name="motPass">Le mot de passe entré.</param>
	/// <param name="ligne">La ligne ou l'usager a été trouvée, -1 si pas trouver.</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gardées</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier);
	/// <summary>
	/// Obtient les scores spécifié de l'usager spécifié. Max: 10
	/// </summary>
	/// <param name="user">L'usager spécifier.</param>
	/// <param name="score">Le score spécifier.</param>
	/// <param name="emplacementSauvegarde">L'emplacement sauvegarde.</param>
	/// <returns>Les scores spécifiés de l'usager spécifié. Max: 10</returns>
	static std::vector<Modele::TopScore> GetTopTenResult(std::string user, int score, std::string emplacementSauvegarde);
	/// <summary>
	/// Obtient les meilleurs scores de l'utilisateur. Max: 10
	/// </summary>
	/// <param name="user">L'usager spécifier.</param>
	/// <param name="emplacementSauvegarde">L'emplacement sauvegarde.</param>
	/// <returns>Les 10 meilleurs scores de l'utilisateur</returns>
	static std::vector<Modele::TopScore> GetTopTenResult(std::string user, std::string emplacementSauvegarde);
	/// <summary>
	/// Obtient les utilisateurs qui ont le score spécifié. Max: 10
	/// </summary>
	/// <param name="score">le score spécifié.</param>
	/// <param name="emplacementSauvegarde">L'emplacement sauvegarde.</param>
	/// <returns>Les utilisateurs ayant le resultat. Max: 10</returns>
	static std::vector<Modele::TopScore> GetTopTenResult(int score, std::string emplacementSauvegarde);
	/// <summary>
	/// Obtient les meilleurs scores. Max: 10
	/// </summary>
	/// <param name="emplacementSauvegarde">L'emplacement sauvegarde.</param>
	/// <returns>Les meilleurs scores. Max: 10</returns>
	static std::vector<Modele::TopScore> GetTopTenResult(std::string emplacementSauvegarde);
	/// <summary>
	/// Détermine si l'utilisateur existe.
	/// </summary>
	/// <param name="user">L'utilisateur.</param>
	/// <param name="emplacementFichier">l'emplacement du fichier de sauvegarde.</param>
	/// <param name="ligne">La ligne ou l'utilisateur a été trouvé, -1 si pas trouver.</param>
	/// <returns></returns>
	static bool UserExist(std::string user, std::string emplacementFichier, int& ligne);
	/// <summary>
	/// Ajouter un score à l'utilisateur.
	/// </summary>
	/// <param name="user">L'utilisateur.</param>
	/// <param name="score">Le resultat.</param>
	/// <param name="emplacement">L'emplacement</param>
	/// <returns>Si le score a été ajouté.</returns>
	static bool AjouterScore(std::string user, int score, std::string emplacement);
};

