#include "SceneNiveau1.h"
#include "Mur.h"
#include "BlocFin.h"
#include "SpawnerMen.h"
#include "SpawnerMen2.h"
#include "SpawnerZombie.h"

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
	
	
	for(int i = 1; i < NOMBRE_TUILES_Y; i++)
	{
		grilleDeTuiles[NOMBRE_TUILES_X - 1][NOMBRE_TUILES_Y - i - 1] = new BlocFin();
		grilleDeTuiles[NOMBRE_TUILES_X - 1][NOMBRE_TUILES_Y - i - 1]->setPosition((NOMBRE_TUILES_X - 1)* TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - i - 1));
	}
	Gem gem;
	gem.setPosition(100, 300);
	gems.push_back(gem);
	gem.setPosition(300, 300);
	gems.push_back(gem);
	//Position arbitraire pour le joueur en x, pas arbitraire en y (sur le plancher)
	joueur.setPosition(100, window->getSize().y - TAILLE_TUILES_Y * 2);
	grilleDeTuiles[10][NOMBRE_TUILES_Y - 2] = new SpawnerMen();
	grilleDeTuiles[10][NOMBRE_TUILES_Y - 2]->setPosition((10)* TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 2));
	grilleDeTuiles[20][NOMBRE_TUILES_Y - 2] = new SpawnerMen2();
	grilleDeTuiles[20][NOMBRE_TUILES_Y - 2]->setPosition((20)* TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 2));
	grilleDeTuiles[30][NOMBRE_TUILES_Y - 2] = new SpawnerZombie();
	grilleDeTuiles[30][NOMBRE_TUILES_Y - 2]->setPosition((30)* TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 2));
	enemies[0] = dynamic_cast<SpawnerMen*>(grilleDeTuiles[10][NOMBRE_TUILES_Y - 2])->Spawn();
	enemies[2] = dynamic_cast<SpawnerMen2*>(grilleDeTuiles[20][NOMBRE_TUILES_Y - 2])->Spawn();
	enemies[1] = dynamic_cast<SpawnerZombie*>(grilleDeTuiles[30][NOMBRE_TUILES_Y - 2])->Spawn();
	for (int i = 0; i<nbEnemies; i++)
	{
		if (!enemies[i]->init(limiteGauche, limiteDroite))
		{
			return false;
		}
		enemies[i]->directionGauche = true;
		enemies[i]->tempsDirection = 0;
	}
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

