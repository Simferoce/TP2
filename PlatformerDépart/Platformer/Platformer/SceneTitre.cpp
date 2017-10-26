#include <algorithm>
#include "Controle.h"
#include "SceneTitre.h"
using namespace platformer;

SceneTitre::SceneTitre()
{

}

SceneTitre::~SceneTitre()
{
}

Scene::scenes SceneTitre::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneTitre::init(RenderWindow * const window)
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

	this->mainWin = window;
	menuInstruction.setFont(font);
	menuInstruction.setString("Enter:Valider|1:Gestion de Compte|2:Meilleurs Scores");
	menuInstruction.setCharacterSize(24);
	menuInstruction.setFillColor(sf::Color::White);
	menuInstruction.setStyle(sf::Text::Bold);
	
	menuInstruction.setPosition((mainWin->getView().getSize().x - menuInstruction.getLocalBounds().width)/2, 0);
	isRunning = true;

	return true;
}

void SceneTitre::getInputs()
{
	enterActif = false;
	backspaceActif = false;
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
			
		}
		if (event.type == Event::KeyPressed)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SC�NE (Vous pouviez vous codez un bouton si �a vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true;
				isRunning = false;
				transitionVersScene = Scene::scenes::LOGIN;
			}
			else if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Numpad1)
			{
				isRunning = false;
				transitionVersScene = Scene::scenes::GESTIONCOMPTE;
			}
			else if (event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Numpad2)
			{
				isRunning = false;
				transitionVersScene = Scene::scenes::SCORE;
			}
		}
	}
}

void SceneTitre::update()
{
}

void SceneTitre::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	mainWin->draw(menuInstruction);
	mainWin->display();
}