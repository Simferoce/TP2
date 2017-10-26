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

std::string Controle::GetText(Modele::StringId id)
{
	if (Modele::dictionnaire.count(id))
		return Modele::GetText(id);
	else
		throw std::invalid_argument("Aucune clef pour " + id);
}

Modele::ResultatAuthentification Controle::AuthentifierUtilisateur(std::string utilisateur, std::string motPass, int& ligne, std::string emplacementFichier)
{
	if (utilisateur.length() < 3 || utilisateur.length() > 25)
		return Modele::UtilisateurFormat;
	if (motPass.length() < 5 || motPass.length() > 15)
		return Modele::MotPassFormat;
	ligne = 0;
	return Modele::AuthentifierUtilisateur(utilisateur,motPass,ligne,emplacementFichier);
}

std::vector<std::string> Controle::split(std::string stringASplit, char caractereQuiSplit)
{
	return Modele::split(stringASplit,caractereQuiSplit);
}
