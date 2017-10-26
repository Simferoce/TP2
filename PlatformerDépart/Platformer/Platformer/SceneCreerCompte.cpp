
#include <algorithm>
#include <fstream>
#include "Modele.h"
#include "SceneCreerCompte.h"

using namespace platformer;

SceneCreerCompte::SceneCreerCompte()
{

}

SceneCreerCompte::~SceneCreerCompte()
{
}

Scene::scenes SceneCreerCompte::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneCreerCompte::init(RenderWindow * const window)
{
	//test de texte � l'�cran
	text1=Modele::CreateTextLine("Veuiller entrer vos informations.",0,0);
	text2=Modele::CreateTextLine("Utilisateur", 0, 50);
	text3=Modele::CreateTextLine("Mot de passe", 0, 100);
	text4=Modele::CreateTextLine("Prenom", 0, 150);
	text5=Modele::CreateTextLine("Nom", 0, 200);
	text6=Modele::CreateTextLine("Courriel", 0, 250);
	



	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'�cran
	textboxUsername.init(480, 24, Vector2f(430, 320), font);
	textbox.init(480, 24, Vector2f(430, 360), font);
	textboxErreur.initInfo(Vector2f(430, 290), font, true);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneCreerCompte::getInputs()
{
	enterActif = false;
	backspaceActif = false;
	for (auto iter = boutonMenu.begin(); iter != boutonMenu.end(); ++iter)
		iter->second = false;
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
				if(textboxActif!=nullptr)
				{
					textboxActif->deSelectionner();
					textboxActif = nullptr;
				}	
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


			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caract�re
			}
		}
		if (event.type == Event::KeyPressed && textboxActif == nullptr)
		{
			//On n'a pas besoin d'une touche pour aller sur la page qu'on est d�j�
			if (event.key.code == Keyboard::Num1)
			{
				boutonMenu[Keyboard::Key::Num1] = true;
				isRunning = false;
				transitionVersScene = Scene::scenes::GESTIONCOMPTE;
			}
			if (event.key.code == Keyboard::Num2) {
				//isRunning = false;
				//transitionVersScene = Scene::scenes::GESTIONCOMPTE;
			}
			else if (event.key.code == Keyboard::Num2)
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
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre � vous d'aller plus loin si vous voulez)
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
}

void SceneCreerCompte::update()
{

}

void SceneCreerCompte::draw()
{
	mainWin->clear();
	textbox.dessiner(mainWin);
	textboxUsername.dessiner(mainWin);
	textboxErreur.dessiner(mainWin);
	//test texte � l'�cran
	// puis, dans la boucle de dessin, entre window.clear() et window.display()
	mainWin->draw(text1);
	mainWin->draw(text2);
	mainWin->draw(text3);
	mainWin->draw(text4);
	mainWin->draw(text5);
	mainWin->draw(text6);

	mainWin->display();
}