#include "SceneNiveau1.h"
#include "Mur.h"

using namespace platformer;

SceneNiveau1::SceneNiveau1() : SceneNiveau(NOMBRE_TUILES_X, NOMBRE_TUILES_Y)
{
}

SceneNiveau1::~SceneNiveau1()
{
}

Scene::scenes SceneNiveau1::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneNiveau1::init(RenderWindow * const window)
{
	if (!SceneNiveau::init(window))
		return false;
	for (int x = 0; x < NOMBRE_TUILES_X; x++)
	{
		//Choix du bloc au hasard
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1] = new Mur();
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1]->setPosition(x * TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 1));
	}
	grilleDeTuiles[NOMBRE_TUILES_X - 3][NOMBRE_TUILES_Y - 2] = new Mur();
	grilleDeTuiles[NOMBRE_TUILES_X - 3][NOMBRE_TUILES_Y - 2]->setPosition((NOMBRE_TUILES_X -3 )* TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 2));
	grilleDeTuiles[NOMBRE_TUILES_X - 6][NOMBRE_TUILES_Y - 5] = new Mur();
	grilleDeTuiles[NOMBRE_TUILES_X - 6][NOMBRE_TUILES_Y - 5]->setPosition((NOMBRE_TUILES_X - 6)* TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 5));
	//Position arbitraire pour le joueur en x, pas arbitraire en y (sur le plancher)
	joueur.setPosition(100, window->getSize().y - TAILLE_TUILES_Y * 2);
	return true;
}


void platformer::SceneNiveau1::getInput()
{
	SceneNiveau::getInput();
}

void SceneNiveau1::update()
{
	SceneNiveau::update();
}

void platformer::SceneNiveau1::drawDefault()
{
	SceneNiveau::drawDefault();
}

