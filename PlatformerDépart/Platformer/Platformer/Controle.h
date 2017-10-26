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
	/// <Controleur> Authentifier l'utilisateur en vérifiant la correspondance entre l'utilisateur et le mot de passe entré.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur à vérifier.</param>
	/// <param name="motPass">Le mot de passe entré.</param>
	/// <param name="ligne">La ligne ou l'usager a été trouvée</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gardées</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier);
};

