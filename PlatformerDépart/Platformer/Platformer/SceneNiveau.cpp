#include "SceneNiveau.h"
#include "Mur.h"
#include "Modele.h"
#include <fstream>
#include "BlocFin.h"


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
		for(int i=0;i<nbEnemies;i++)
		{
			delete enemies[i];
		}
	}
	Scene::scenes SceneNiveau::run()
	{
		return scenes();
	}
	bool SceneNiveau::init(RenderWindow * const window)
	{
		score = 0;
		scoreText.setFont(Modele::GetFont());
		scoreText.setFillColor(Modele::TEXTE_COULEUR);
		scoreText.setStyle(Modele::TEXTE_STYLE);
		scoreText.setCharacterSize(Modele::GROSSEUR_CARACTERE);
		scoreText.setString(Modele::GetText(Modele::PointageJeu) + std::to_string(score));
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
		//initialisation des ennemis
		for(int i=0;i<nbEnemies;i++)
		{
			if (!enemies[i]->init(limiteGauche, limiteDroite))
			{
				return false;
			}
			enemies[i]->directionGauche = true;
			enemies[i]->tempsDirection = 0;
		}
		delaiDeuxiemeAttaqueZombie = 0;
		if (!joueur.init(limiteGauche, limiteDroite))
		{
			return false;
		}
		if (!Gem::init())
			return  false;
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
		//Deplacement
		joueur.velocity.x = 0;
		Joueur::AnimationEnum anime = Joueur::Attend;
		if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
		{
			if(!joueur.jumped)
				anime = Joueur::Cours;
			joueur.sensJoueurEst = Joueur::Direction::Gauche;
			joueur.velocity.x = -joueur.vitesse;
		}
		else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
		{
			if (!joueur.jumped)
				anime = Joueur::Cours;
			joueur.sensJoueurEst = Joueur::Direction::Droite;
			joueur.velocity.x = joueur.vitesse;
		}
		if(inputs[Keyboard::Space])
		{
			joueur.Jump();
		}
		if (joueur.jumped) anime = Joueur::AnimationEnum::Saute;
		joueur.UpdateTexture(anime);
		joueur.move(joueur.velocity.x, joueur.velocity.y);
		joueur.velocity.y += gravite;
		//Collision bloc/joueur
		for(int i =0; i < NOMBRE_TUILES_X; ++i)
		{
			for (int j = 0; j < NOMBRE_TUILES_Y; ++j)
			{
				if(grilleDeTuiles[i][j] != nullptr)
				{
					Bloc::Collision collide = grilleDeTuiles[i][j]->DetermineCollision(joueur.getGlobalBounds(), joueur.velocity);
					if(BlocFin* endingBloc = dynamic_cast<BlocFin*>(grilleDeTuiles[i][j]))
					{
						if (!(collide == Bloc::CollisionWithNoDeterminateSide || collide == Bloc::None))
						{
							isRunning = false;
							transitionVersScene = Scene::scenes::TITRE;
						}
					}
					switch (collide)
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
		//Collision enemy/joueur
		for(int i=0;i<nbEnemies;i++)
		{
			//Si l'ennemi est vivant
			if(enemies[i]->nbVies>0)
			{
				//ennemi touche le joueur
				if (enemies[i]->getPosition().x + 1 >= joueur.getPosition().x && enemies[i]->getPosition().x <= joueur.getPosition().x + 1 &&
					enemies[i]->getPosition().y == joueur.getPosition().y)
				{
					isRunning = false;
					transitionVersScene = Scene::scenes::TITRE;
				}
				//Saut sur un ennemi
				else if (enemies[i]->getPosition().x + 5 >= joueur.getPosition().x && enemies[i]->getPosition().x <= joueur.getPosition().x + 5 &&
					enemies[i]->getPosition().y+10 >= joueur.getPosition().y && delaiDeuxiemeAttaqueZombie>100)
				{
					enemies[i]->nbVies--;
					delaiDeuxiemeAttaqueZombie = 0;
				}
				//ennemi mort
				if(enemies[i]->nbVies==0)
				{
					score += 5;
				}
				//compteur pour s'assurer que les 2 vies du zombie soient visibles au joueur
				delaiDeuxiemeAttaqueZombie++;
			}			
		}
		//Enemy (code actuel à cause que Move de Men n'est pas appelé à la place de move de enemy)
		for(int z=0;z<nbEnemies;z++)
		{
			if(enemies[z]->nbVies>0)
			{
				enemies[z]->velocity.x = 0;
				Enemy::AnimationEnum animeEnemy = Enemy::Attend;
				if (enemies[z]->directionGauche == true)
				{
					if (enemies[z]->typeActuel == Enemy::typeEnemy::MEN || enemies[z]->typeActuel == Enemy::typeEnemy::ZOMBIE)
					{
						if (!enemies[z]->jumped)
							animeEnemy = Enemy::Cours;
						enemies[z]->sensJoueurEst = Enemy::Direction::Gauche;
						enemies[z]->velocity.x = -enemies[z]->vitesse;
						if (enemies[z]->tempsDirection>80)
						{
							enemies[z]->tempsDirection = 0;
							enemies[z]->directionGauche = false;
						}
						else
						{
							enemies[z]->tempsDirection++;
						}
					}
				}
				else
				{
					if (enemies[z]->typeActuel == Enemy::typeEnemy::MEN || enemies[z]->typeActuel == Enemy::typeEnemy::ZOMBIE)
					{
						if (!enemies[z]->jumped)
							animeEnemy = Enemy::Cours;
						enemies[z]->sensJoueurEst = Enemy::Direction::Droite;
						enemies[z]->velocity.x = enemies[z]->vitesse;
						if (enemies[z]->tempsDirection>80)
						{
							enemies[z]->tempsDirection = 0;
							enemies[z]->directionGauche = true;
						}
						else
						{
							enemies[z]->tempsDirection++;
						}
					}
				}
				if (enemies[z]->typeActuel == Enemy::typeEnemy::MEN2)
				{
					if (enemies[z]->tempsDirection>100)
					{
						enemies[z]->Jump();
						enemies[z]->tempsDirection = 0;
					}
					else
					{
						enemies[z]->tempsDirection++;
					}
				}
				if (enemies[z]->jumped) animeEnemy = Enemy::AnimationEnum::Saute;
				enemies[z]->UpdateTexture(animeEnemy);
				enemies[z]->move(enemies[z]->velocity.x, enemies[z]->velocity.y);
				enemies[z]->velocity.y += gravite;
				//Collision bloc/enemy
				for (int i = 0; i < NOMBRE_TUILES_X; ++i)
				{
					for (int j = 0; j < NOMBRE_TUILES_Y; ++j)
					{
						if (grilleDeTuiles[i][j] != nullptr)
						{
							Bloc::Collision collide = grilleDeTuiles[i][j]->DetermineCollision(enemies[z]->getGlobalBounds(), enemies[z]->velocity);
							if (BlocFin* endingBloc = dynamic_cast<BlocFin*>(grilleDeTuiles[i][j]))
							{
								if (!(collide == Bloc::CollisionWithNoDeterminateSide || collide == Bloc::None))
								{
									isRunning = false;
									transitionVersScene = Scene::scenes::TITRE;
								}
							}
							switch (collide)
							{
							case Bloc::Collision::None:
								break;
							case Bloc::Collision::Bot:
								enemies[z]->velocity.y = 0;
								enemies[z]->setPosition(enemies[z]->getPosition().x, grilleDeTuiles[i][j]->getPosition().y + grilleDeTuiles[i][j]->getGlobalBounds().height);
								break;
							case Bloc::Collision::Top:
								enemies[z]->velocity.y = 0;
								enemies[z]->setPosition(enemies[z]->getPosition().x, grilleDeTuiles[i][j]->getPosition().y - enemies[z]->getGlobalBounds().height);
								enemies[z]->jumped = false;
								break;
							case Bloc::Collision::Left:
								enemies[z]->velocity.x = 0;
								enemies[z]->setPosition(grilleDeTuiles[i][j]->getPosition().x - enemies[z]->getGlobalBounds().width, enemies[z]->getPosition().y);
								break;
							case Bloc::Collision::Right:
								enemies[z]->velocity.x = 0;
								enemies[z]->setPosition(grilleDeTuiles[i][j]->getPosition().x + grilleDeTuiles[i][j]->getGlobalBounds().width, enemies[z]->getPosition().y);
								break;
							case Bloc::Collision::CollisionWithNoDeterminateSide:
								break;
							}
						}
					}
				}
			}
			
		}
		
		//Vue
		if(joueur.getPosition().x - vue.getSize().x / 2 > limiteGauche && joueur.getPosition().x + vue.getSize().x / 2 < limiteDroite)
		{
			vue.setCenter(joueur.getPosition().x, vue.getCenter().y);
			scoreText.setPosition(vue.getCenter().x - vue.getSize().x / 2, scoreText.getPosition().y);
		}
		std::vector<Gem*> toDelete;
		for(auto iter = gems.begin(); iter != gems.end();)
		{
			if (iter->getGlobalBounds().intersects(joueur.getGlobalBounds()))
			{
				iter = gems.erase(iter);
				score++;
			}
			else
				++iter;
		}
		scoreText.setString(Modele::GetText(Modele::PointageJeu) + std::to_string(score));
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
		for(Gem gem : gems)
			mainWin->draw(gem);
		mainWin->draw(joueur);
		for(int i=0;i<nbEnemies;i++)
		{
			//si l'ennemi est vivant
			if(enemies[i]->nbVies>0)
			{
				mainWin->draw(*enemies[i]);
			}		
		}	
		mainWin->draw(scoreText);
	}
	int SceneNiveau::GetScore()
	{
		return score;
	}
}
