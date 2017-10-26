#include "SceneGestionCompte.h"
#include <algorithm>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace platformer;

SceneGestionCompte::SceneGestionCompte()
{

}

SceneGestionCompte::~SceneGestionCompte()
{
}

Scene::scenes SceneGestionCompte::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneGestionCompte::init(RenderWindow * const window)
{
	//http://www.cplusplus.com/forum/beginner/8388/
	ifstream iFich;
	iFich.open("userpass.txt");
	if (!iFich.is_open())
	{
		//cout << "Fichier au mauvais endroit" << endl;
		return 0;
	}
	//pointATrouver = strtok(ligne, ':');
	while(getline(iFich, ligne))
	{
		int trouve = ligne.find(":");
		for(int i=0; i<trouve;i++)
		{
			utilisateur += ligne[i];
		}
	}
	//Lecture ligne
	/*char ligneTemp[100] = ligne;
	char utilisateurTab[] = ligne;
	pointATrouver = strtok(utilisateurTab, ':');*/
	//utilisateur = ligne;

	//test de texte � l'�cran
	text.setFont(font); 
	text.setString("Appuyer sur telle partie du texte pour voir votre score,\n changer votre nom ou mot de passe ou retourner");
	text.setCharacterSize(24);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	
	if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	ecranTitre.setTexture(ecranTitreT);

	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'�cran
	textboxUsername.init(480, 24, Vector2f(430, 320), font);
	textbox.init(480, 24, Vector2f(430, 360), font);
	textboxErreur.initInfo(Vector2f(430, 290), font, true);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneGestionCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin � l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un �v�nement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche � la textbox avec la souris
			if (textbox.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textbox; //Ce textbox devient actif
				textbox.selectionner();  //on l'affiche comme �tant s�lectionn�
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis �a fait clean si on fait un nouvel essai)
			}
			else if (textboxUsername.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxUsername; //Ce textbox devient actif
				textboxUsername.selectionner();  //on l'affiche comme �tant s�lectionn�
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis �a fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait �tre dans toutes vos fen�tres o� il n'y a pas de textbox.
				textboxActif = nullptr;
				textboxUsername.deSelectionner();
			}
		}

		//Un �v�nement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SC�NE (Vous pouviez vous codez un bouton si �a vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caract�re

								   //Condition bison pour voir que la transition fonctionne.
				if (textbox.getTexte() == "password")
				{
					isRunning = false;
					transitionVersScene = Scene::scenes::NIVEAU1;
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Mauvais mot de passe, entrez-en un bon!");
				}
			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caract�re
			}
		}
		if(event.type == Event::KeyPressed)
		{
			//On n'a pas besoin d'une touche pour aller sur la page qu'on est d�j�
			/*if (event.key.code == Keyboard::Num1)
			{
				boutonMenu[Keyboard::Key::Num1] = true;
				isRunning = false;
				transitionVersScene = Scene::scenes::GESTIONCOMPTE;
			}*/
			if (event.key.code == Keyboard::Num2)
			{
				boutonMenu[Keyboard::Key::Num2] = true;
			}
			else if (event.key.code == Keyboard::Num3)
			{
				boutonMenu[Keyboard::Key::Num3] = true;
			}
		}
		const auto menuBoutonChoisi = std::find_if(boutonMenu.begin(), boutonMenu.end(), [](std::pair<Keyboard::Key, bool> n) { return n.second == true; });
		//Attention : TextEntered est diff�rent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.4/window-events-fr.php
		if (menuBoutonChoisi == boutonMenu.end() && !backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre � vous d'aller plus loin si vous voulez)
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
		//Dans tous les cas on netoie ces conditions apr�s chaque boucle.
		enterActif = false;
		backspaceActif = false;
		for (auto iter = boutonMenu.begin(); iter != boutonMenu.end(); ++iter)
			iter->second = false;
}

void SceneGestionCompte::update()
{
}

void SceneGestionCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textbox.dessiner(mainWin);
	textboxUsername.dessiner(mainWin);
	textboxErreur.dessiner(mainWin);
	//test texte � l'�cran
	// puis, dans la boucle de dessin, entre window.clear() et window.display()
	mainWin->draw(text);

	mainWin->display();
}