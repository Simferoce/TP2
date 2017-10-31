#include "SceneNiveau1.h"

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
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1]->setPosition(x * TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 1));
	}

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

