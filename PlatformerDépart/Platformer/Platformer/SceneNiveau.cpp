#include "SceneNiveau.h"
#include "Mur.h"


namespace platformer
{
	float SceneNiveau::gravite = 0.4f;
	SceneNiveau::SceneNiveau(int nbreX, int nbreY) : NOMBRE_TUILES_X(nbreX), NOMBRE_TUILES_Y(nbreY), limiteDroite(nbreX*TAILLE_TUILES_X)
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
		for(int  i = 0; i < nbreBackground; i++)
		{
			for(int j =0; j < BACKGROUNDS; j++)
			{
				if (background[i][j] != nullptr)
				{
					delete background[i][j];
				}
			}
			delete[] background[i];
		}
		delete[] background;
	}
	Scene::scenes SceneNiveau::run()
	{
		return scenes();
	}
	bool SceneNiveau::init(RenderWindow * const window)
	{
		vue = window->getDefaultView();
		window->setView(vue);
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
		nbreBackground = limiteDroite / backgroundT[0].getSize().x;
		background = new Sprite**[nbreBackground];
		for (int i = 0; i < nbreBackground; i++)
		{
			background[i] = new Sprite*[BACKGROUNDS];
			for (int j = 0; j < BACKGROUNDS; j++)
			{
				background[i][j] = new Sprite(backgroundT[j]);
				if(i % 2 == 1)
					background[i][j]->setTextureRect(sf::IntRect(background[i][j]->getGlobalBounds().width, 0, -background[i][j]->getGlobalBounds().width, background[i][j]->getGlobalBounds().height));
				background[i][j]->setPosition(i * backgroundT[0].getSize().x, 0);
			}
		}
		if (!joueur.init(limiteGauche, limiteDroite, "Ressources\\Sprites\\Player\\Player.png"))
		{
			return false;
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
		joueur.velocity.x = 0;
		if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
		{
			joueur.velocity.x = -joueur.vitesse;
		}
		else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
		{
			joueur.velocity.x = joueur.vitesse;
		}
		if(inputs[Keyboard::Space])
		{
			joueur.jump();
		}
		joueur.move(joueur.velocity.x, joueur.velocity.y);
		joueur.velocity.y += gravite;
		//TO DO Déterminer les blocs que le joueur touche à la place de vérifie si un bloc touche le joueur.
		for(int i =0; i < NOMBRE_TUILES_X; ++i)
		{
			for (int j = 0; j < NOMBRE_TUILES_Y; ++j)
			{
				if(grilleDeTuiles[i][j] != nullptr && dynamic_cast<Mur*>(grilleDeTuiles[i][j]) != nullptr)
				{
					switch (grilleDeTuiles[i][j]->DetermineCollision(joueur.getGlobalBounds(), joueur.velocity))
					{
					case Bloc::Collision::None:
						break;
					case Bloc::Collision::Bot:
						joueur.velocity.y = 0;
						joueur.setPosition(joueur.getPosition().x, grilleDeTuiles[i][j]->getPosition().y + grilleDeTuiles[i][j]->getGlobalBounds().height);
						break;
					case Bloc::Collision::Top:
						joueur.velocity.y = 0;
						joueur.setPosition(joueur.getPosition().x, grilleDeTuiles[i][j]->getPosition().y - joueur.getGlobalBounds().height);
						joueur.jumped = false;
						break;
					case Bloc::Collision::Left:
						joueur.velocity.x = 0;
						joueur.setPosition(grilleDeTuiles[i][j]->getPosition().x - joueur.getGlobalBounds().width, joueur.getPosition().y);
						break;
					case Bloc::Collision::Right:
						joueur.velocity.x = 0;
						joueur.setPosition(grilleDeTuiles[i][j]->getPosition().x + grilleDeTuiles[i][j]->getGlobalBounds().width, joueur.getPosition().y);
						break;
					case Bloc::Collision::CollisionWithNoDeterminateSide:
						break;
					}
				}
			}
		}
		if(joueur.getPosition().x - vue.getSize().x / 2 > limiteGauche && joueur.getPosition().x + vue.getSize().x / 2 < limiteDroite)
		{
			vue.setCenter(joueur.getPosition().x, vue.getCenter().y);
		}
		mainWin->setView(vue);
	}
	void SceneNiveau::draw()
	{
		mainWin->clear();
		drawDefault();
		mainWin->display();
	}
	void SceneNiveau::drawDefault()
	{
		for (int i = 0; i < nbreBackground; i++)
		{
			for (int j = 0; j < BACKGROUNDS; j++)
			{
				mainWin->draw(*background[i][j]);
			}
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
