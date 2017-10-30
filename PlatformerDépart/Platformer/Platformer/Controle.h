#pragma once
#include <string>
#include "Modele.h"
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
	static bool UserExist(std::string user, std::string emplacementFichier, int& ligne);
};

