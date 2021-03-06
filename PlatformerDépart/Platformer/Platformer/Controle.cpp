#pragma once
#include "Controle.h"
#include "Modele.h"
Controle* Controle::instance = nullptr;

void Controle::Decharger()
{

	delete instance;
	instance = nullptr;
}

Controle::Controle()
{
}

Controle* Controle::GetInstance()
{
	if (instance == nullptr)
		instance = new Controle();
	return instance;
}
bool Controle::AjouterScore(std::string user, int score, std::string emplacement)
{
	int ligne = 0;
	if (UserExist(user, emplacement, ligne) && score >= 0)
		 return Modele::AjouterScore(user, score, emplacement);
	else
		 return false;
}


std::string Controle::GetText(Modele::StringId id)
{
	if (Modele::dictionnaire.count(id))
		return Modele::GetText(id);
	else
		throw std::invalid_argument("Aucune clef pour " + id);
}

Modele::ResultatAuthentification Controle::AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier)
{
	if (utilisateur.length() < Modele::MIN_NICKNAME_LENGTH || utilisateur.length() > Modele::MAX_NICKNAME_LENGTH)
	{
		ligne = -1;
		return Modele::UtilisateurFormat;
	}
		
	if (motPass.length() < Modele::MIN_PASSWORD_LENGTH || motPass.length() > Modele::MAX_PASSWORD_LENGTH)
	{
		ligne = -1;
		return Modele::MotPassFormat;
	}
	return Modele::AuthentifierUtilisateur(utilisateur,motPass,ligne,emplacementFichier);
}

std::vector<Modele::TopScore> Controle::GetTopTenResult(std::string user, int score, std::string emplacementSauvegarde)
{
	int ligne;
	if (score >= 0 && UserExist(user, emplacementSauvegarde, ligne))
		return Modele::GetTopTenResult(user, score, emplacementSauvegarde);
	else
		return std::vector<Modele::TopScore>();
}

std::vector<Modele::TopScore> Controle::GetTopTenResult(std::string user, std::string emplacementSauvegarde)
{
	int ligne;
	if (UserExist(user, emplacementSauvegarde, ligne))
		return Modele::GetTopTenResult(user, emplacementSauvegarde);
	else
		return std::vector<Modele::TopScore>();

}

std::vector<Modele::TopScore> Controle::GetTopTenResult(int score, std::string emplacementSauvegarde)
{
	if (score >= 0)
		return Modele::GetTopTenResult(score, emplacementSauvegarde);
	else
		return std::vector<Modele::TopScore>();
}

std::vector<Modele::TopScore> Controle::GetTopTenResult(std::string emplacementSauvegarde)
{
	return Modele::GetTopTenResult(emplacementSauvegarde);
}

bool Controle::UserExist(std::string user, std::string emplacementFichier, int& ligne)
{
	if (user.length() > Modele::MAX_NICKNAME_LENGTH || user.length() < Modele::MIN_NICKNAME_LENGTH)
	{
		ligne = -1;
		return false;
	}
	return Modele::UserExist(user, emplacementFichier, ligne);
}

std::vector<std::string> Controle::split(std::string stringASplit, char caractereQuiSplit)
{
	return Modele::split(stringASplit,caractereQuiSplit);
}
