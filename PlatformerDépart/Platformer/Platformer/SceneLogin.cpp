#include "SceneLogin.h"
#include <algorithm>
#include "Controle.h"
using namespace platformer;

SceneLogin::SceneLogin()
{
	
}

SceneLogin::~SceneLogin()
{
}

Scene::scenes SceneLogin::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneLogin::init(RenderWindow * const window)
{
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
	//par rapport au fond d'écran
	textboxUsername.init(480, 24, Vector2f(430, 320), font);
	textbox.init(480, 24, Vector2f(430, 360), font);
	textboxErreur.initInfo(Vector2f(430, 290), font, true);
	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneLogin::getInputs()
{
	enterActif = false;
	backspaceActif = false;
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textboxUser avec la souris
			if (textbox.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textbox; //Ce textboxUser devient actif
				textbox.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxUsername.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxUsername; //Ce textboxUser devient actif
				textboxUsername.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textboxUser actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textboxUser.
				if(textboxActif != nullptr)
					textboxActif->deSelectionner();
				textboxActif = nullptr;
			}
		}
		if (event.type == Event::KeyPressed)
		{						
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère
			}
		}
		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
		}
		if (event.type == Event::KeyPressed && textboxActif == nullptr)
		{
			if(event.key.code == Keyboard::Key::Escape)
			{
				transitionVersScene = Scene::scenes::TITRE;
				isRunning = false;
			}
		}
		//Attention : TextEntered est différent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.4/window-events-fr.php
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre à vous d'aller plus loin si vous voulez)
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
}

void SceneLogin::update()
{
	if(enterActif)
	{
		int ligne = 0;
		Modele::ResultatAuthentification resultat = Controle::AuthentifierUtilisateur(textboxUsername.getTexte(), textbox.getTexte(), ligne, "userpass.txt");
		if (Modele::ResultatAuthentification::Reussi == resultat)
		{
			transitionVersScene = Scene::scenes::NIVEAU1;
			isRunning = false;
		}
		else 
		{
			textboxErreur.insererTexte("Mot de passe ou nom d'utilisateur incorrecte.");
		}
	}
}

void SceneLogin::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textbox.dessiner(mainWin);
	textboxUsername.dessiner(mainWin);
	textboxErreur.dessiner(mainWin);
	mainWin->display();
}