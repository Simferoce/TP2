#pragma once
#include <SFML/Graphics.hpp>
#include "Joueur.h"
#include "SceneNiveau.h"

using namespace sf;

namespace platformer
{
	class SceneNiveau1 : public SceneNiveau
	{
	public:
		SceneNiveau1();
		~SceneNiveau1();

		scenes run();
		bool init(RenderWindow * const window);
		void getInput() override;
		void update() override;
		void drawDefault() override;
	private:
		static const int NOMBRE_TUILES_X = 20;
		static const int NOMBRE_TUILES_Y = 15;
	};
}