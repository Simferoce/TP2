#include "SceneGestionCompte.h"
#include <algorithm>
#include <fstream>
#include "Modele.h"

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
	/*ifstream iFich;
	iFich.open("userpass.txt");
	if (!iFich.is_open())
	{
		//cout << "Fichier au mauvais endroit" << endl;
		return 0;
	}
	while(getline(iFich, ligne))
	{
		information = Modele::split(ligne, ':');
		if()
	}*/

	//test de texte à l'écran
	text.setFont(font); 
	text.setString("Appuyer 1 pour creer un compte, \n2 pour modifier votre compte, \n 3 pour le supprimer ou \n 4 pour l.");
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
	//par rapport au fond d'écran
	textboxUsername.init(480, 24, Vector2f(430, 320), font);
	textbox.init(480, 24, Vector2f(430, 360), font);
	textboxErreur.initInfo(Vector2f(430, 290), font, true);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneGestionCompte::getInputs()
{
	enterActif = false;
	backspaceActif = false;
	for (auto iter = boutonMenu.begin(); iter != boutonMenu.end(); ++iter)
		iter->second = false;
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

		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère


			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
		}
		if (event.type == Event::KeyPressed && textboxActif == nullptr)
		{
			//On n'a pas besoin d'une touche pour aller sur la page qu'on est déjà
			if (event.key.code == Keyboard::Num1)
			{
				boutonMenu[Keyboard::Key::Num1] = true;
				isRunning = false;
			}
				transitionVersScene = Scene::scenes::CREERCOMPTE;
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
	//test texte à l'écran
	// puis, dans la boucle de dessin, entre window.clear() et window.display()
	mainWin->draw(text);

	mainWin->display();
}