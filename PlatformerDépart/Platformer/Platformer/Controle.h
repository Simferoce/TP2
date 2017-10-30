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
	/// Obtient le texte correspondant � l'identifiant
	/// </summary>
	/// <param name="id">Identifiant du texte.</param>
	/// <returns></returns>
	static std::string GetText(Modele::StringId id);
	/// <summary>
	/// Diviser une cha�ne de caract�re.
	/// </summary>
	/// <param name="stringASplit">La cha�ne de caract�re � diviser.</param>
	/// <param name="caractereQuiSplit">Le caract�re qui sert pour la division.</param>
	/// <returns></returns>
	static std::vector<std::string> split(std::string stringASplit, char caractereQuiSplit);
	/// <summary>
	/// <Controleur> Authentifier l'utilisateur en v�rifiant la correspondance entre l'utilisateur et le mot de passe entr�.
	/// </summary>
	/// <param name="utilisateur">L'utilisateur � v�rifier.</param>
	/// <param name="motPass">Le mot de passe entr�.</param>
	/// <param name="ligne">La ligne ou l'usager a �t� trouv�e, -1 si pas trouver.</param>
	/// <param name="emplacmeentFichier">Le fichier ou les infos sont gard�es</param>
	/// <returns></returns>
	static Modele::ResultatAuthentification AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier);
	static bool UserExist(std::string user, std::string emplacementFichier, int& ligne);
};

