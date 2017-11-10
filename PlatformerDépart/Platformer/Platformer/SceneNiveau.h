#pragma once
#include "Scene.h"
#include "Joueur.h"
#include "Bloc.h"
#include "Gem.h"
#include "Enemy.h"

namespace platformer
{
	class SceneNiveau :
		public Scene
	{
	public :
		static const int TUILES_ROUGES = 7;
		static const int BACKGROUNDS = 3;
		static const int TAILLE_TUILES_X = 40;
		static const int TAILLE_TUILES_Y = 32;
	protected:
		int NOMBRE_TUILES_X;
		int NOMBRE_TUILES_Y;
		Bloc*** grilleDeTuiles;
		const int limiteGauche = 0;
		const int limiteDroite = 800;
		std::map<Keyboard::Key, bool> inputs;
		Joueur joueur;
		View vue;
		static float gravite;
		int score;
		Text scoreText;
		std::vector<Gem> gems;
		/// <summary>
		/// Trois backgrounds superposés pour le plus bel effet visuel
		/// </summary>
		Texture backgroundT[BACKGROUNDS];
		Enemy* enemies;
		int nbEnemies = 3;
		Sprite*** background;
		int nbreBackground;
		/// <summary>
		/// On a 7 tuiles rouges de base; alors on va toutes les utiliser, pour le moment.
		/// </summary>
		Texture tuilesRougesT[TUILES_ROUGES];

	public:
		SceneNiveau(int nbreX, int nbreY);
		~SceneNiveau();

		Scene::scenes run();
		virtual bool init(RenderWindow * const window);		
		/// <summary>
		/// Recupère les entrées de utilisateur. Méthode incomplète.
		/// </summary>
		virtual void getInputs();
		virtual void getInput();
		virtual void update();
		virtual void draw();
		virtual void drawDefault();
		int GetScore();
	};
}

