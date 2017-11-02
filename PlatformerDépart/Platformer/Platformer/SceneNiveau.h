#pragma once
#include "Scene.h"
#include "Joueur.h"
#include "Bloc.h"

namespace platformer
{
	class SceneNiveau :
		public Scene
	{
	protected:
		int NOMBRE_TUILES_X;
		int NOMBRE_TUILES_Y;
		static const int TAILLE_TUILES_X = 40;
		static const int TAILLE_TUILES_Y = 32;
		static const int TUILES_ROUGES = 7;
		static const int BACKGROUNDS = 3;
		std::map<Keyboard::Key, bool> inputs;
		Joueur joueur;
		Bloc*** grilleDeTuiles;
		static float gravite;
		/// <summary>
		/// Trois backgrounds superpos�s pour le plus bel effet visuel
		/// </summary>
		Texture backgroundT[BACKGROUNDS];
		Sprite background[BACKGROUNDS];
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
		/// Recup�re les entr�es de utilisateur. M�thode incompl�te.
		/// </summary>
		virtual void getInputs();
		virtual void getInput();
		virtual void update();
		virtual void draw();
		virtual void drawDefault();
	};
}

