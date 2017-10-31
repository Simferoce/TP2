#include "SceneNiveau.h"


namespace platformer
{
	SceneNiveau::SceneNiveau(int nbreX, int nbreY) : NOMBRE_TUILES_X(nbreX), NOMBRE_TUILES_Y(nbreY)
	{
		grilleDeTuiles = new Bloc**[NOMBRE_TUILES_X];
		for (int i = 0; i < NOMBRE_TUILES_X; ++i)
		{
			grilleDeTuiles[i] = new Bloc*[NOMBRE_TUILES_Y];
			for (int j = 0; j < NOMBRE_TUILES_Y; ++j)
				grilleDeTuiles[i][j] = nullptr;
		}
	}
	SceneNiveau::~SceneNiveau()
	{
		for (int x = 0; x < NOMBRE_TUILES_X; x++)
		{
			for (int y = 0; y < NOMBRE_TUILES_Y; y++)
			{
				if (grilleDeTuiles[x][y] != nullptr)
				{
					delete grilleDeTuiles[x][y];
				}
			}
			delete[] grilleDeTuiles[x];
		}
		delete[] grilleDeTuiles;
	}
	Scene::scenes SceneNiveau::run()
	{
		return scenes();
	}
	bool SceneNiveau::init(RenderWindow * const window)
	{
		window->setView(window->getDefaultView());
		this->mainWin = window;
		for (int i = 0; i < TUILES_ROUGES; i++)
		{
			if (!tuilesRougesT[i].loadFromFile("Ressources\\Tiles\\BlockA" + std::to_string(i) + ".png"))
			{
				return false;
			}
		}

		for (int i = 0; i < BACKGROUNDS; i++)
		{
			if (!backgroundT[i].loadFromFile("Ressources\\Backgrounds\\Layer" + std::to_string(i) + "_1.png"))
			{
				return false;
			}
		}

		if (!joueur.init(0, window->getSize().x, "Ressources\\Sprites\\Player\\Player.png"))
		{
			return false;
		}

		for (int i = 0; i < BACKGROUNDS; i++)
		{
			background[i].setTexture(backgroundT[i]);
		}
		isRunning = true;
		srand(time(nullptr));
		return true;
	}
	void SceneNiveau::getInputs()
	{
		while (mainWin->pollEvent(event))
		{
			getInput();
		}
	}
	void SceneNiveau::getInput()
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Scene::scenes::TITRE;
			}
			else
			{
				inputs[event.key.code] = true;
			}
		}
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code != Keyboard::Escape)
				inputs[event.key.code] = false;
		}
	}
	void SceneNiveau::update()
	{
		if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
		{
			joueur.move(-1);
		}
		else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
		{
			joueur.move(1);
		}
	}
	void SceneNiveau::draw()
	{
		mainWin->clear();
		drawDefault();
		mainWin->display();
	}
	void SceneNiveau::drawDefault()
	{
		for (int i = 0; i < BACKGROUNDS; i++)
		{
			mainWin->draw(background[i]);
		}

		for (int x = 0; x < NOMBRE_TUILES_X; x++)
			for (int y = 0; y < NOMBRE_TUILES_Y; y++)
			{
				if (grilleDeTuiles[x][y] != nullptr)
				{
					mainWin->draw(*grilleDeTuiles[x][y]);
				}
			}
		mainWin->draw(joueur);
	}
}