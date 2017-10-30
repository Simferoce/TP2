#pragma once
#include "Scene.h"
#include "Textbox.h"

namespace platformer
{
	class SceneScore :
		public Scene
	{
	public:
		SceneScore();
		~SceneScore();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:

		Textbox textboxUser;
		Textbox textboxScore;
		static const int TABLEAU_SCORE_X = 2;
		static const int TABLEAU_SCORE_Y = 10;
		static const int DISTANCE_ENTRE_SCORE_Y = 35;
		static const int POSITION_BASE_SCORE_X = 35;
		static const int POSITION_BASE_SCORE_Y = 100;
		static const int DISTANCE_ENTRE_SCORE_X = 500;
		static const int LARGEUR_TEXT = 360;
		static const int HAUTEUR_TEXT = 24;
		static const int POSITION_TEXTBOX_X = 600;
		static const int POSITION_TEXTBOX_USER_Y = 20;
		static const int POSITION_TEXTBOX_PASSWORD_Y = 60;
		enum tableauScoreReprensantation { Utilisateur, Score };
		Text tableauScore[TABLEAU_SCORE_X][TABLEAU_SCORE_Y];
		//Nécessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;
		//Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
		Textbox* textboxActif = nullptr;
	};
}

