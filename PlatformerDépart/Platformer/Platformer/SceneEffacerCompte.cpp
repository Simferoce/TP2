#include "Controle.h"
#include "Game.h"
#include "SceneEffacerCompte.h"
using namespace platformer;

	SceneEffacerCompte::SceneEffacerCompte()
	{
		userSupprimer = Game::userConnected;
	}
	SceneEffacerCompte::~SceneEffacerCompte()
	{
		
	}
	Scene::scenes SceneEffacerCompte::run()
	{
		while (isRunning)
		{
			getInputs();
			update();
			draw();
		}

		return transitionVersScene;
	}
	bool SceneEffacerCompte::init(RenderWindow * const window)
	{
		ecranTitre.setTexture(Modele::GetTextureBackground());
		//test
		textMessage = Modele::CreateTextLine("Appuyer sur 1 pour supprimer ou enter pour retourner", 0, 0);
		//Les positions sont arbitraires, obtenus par essai et erreur.
		//par rapport au fond d'écran
		textboxUsername.init(480, 24, Vector2f(430, 320), Modele::GetFont());
		textbox.init(480, 24, Vector2f(430, 360), Modele::GetFont());
		textboxErreur.initInfo(Vector2f(430, 290), Modele::GetFont(), true);
		textboxUsername.insererTexte(userSupprimer);
		this->mainWin = window;
		isRunning = true;

		return true;
	}
	void SceneEffacerCompte::getInputs()
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
					if (textboxActif != nullptr)
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
				if (event.key.code == Keyboard::Key::Escape)
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
	void SceneEffacerCompte::update()
	{
		
		if (event.type == Event::KeyPressed)
		{
			int ligne = 0;
		
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true;
				isRunning = false;
				transitionVersScene = Scene::scenes::TITRE;
			}
			if (event.key.code == Keyboard::Key::Num1)
			{
				enterActif = true;
				isRunning = false;
				if (enterActif)
				{
					if (Modele::UserExist(userSupprimer, "Ressources\\Fonts\\Peric.ttf", ligne))
					{
						//enlever User
					}
				}
				transitionVersScene = Scene::scenes::TITRE;
			}
			
		}
	}

	void SceneEffacerCompte::draw()
	{
		mainWin->clear();
		mainWin->draw(ecranTitre);
		mainWin->draw(textMessage);
		textbox.dessiner(mainWin);
		textboxUsername.dessiner(mainWin);
		textboxErreur.dessiner(mainWin);
		mainWin->display();
	}