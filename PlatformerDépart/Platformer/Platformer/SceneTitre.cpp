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
	ecranTitre.setTexture(Modele::GetTextureBackground());

	this->mainWin = window;
	menuInstruction.setFont(Modele::GetFont());
	menuInstruction.setString("Enter:Valider|1:Gestion de Compte|2:Meilleurs Scores");
	menuInstruction.setCharacterSize(Modele::GROSSEUR_CARACTERE);
	menuInstruction.setFillColor(Modele::TEXTE_COULEUR);
	menuInstruction.setStyle(Modele::TEXTE_STYLE);
	
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
			
		}
		if (event.type == Event::KeyPressed)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
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