#pragma once
//class SceneTitre
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"


using namespace sf;

namespace platformer
{
	class SceneTitre: public Scene
	{
	public:
		SceneTitre();
		~SceneTitre();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		//L'écran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Texture ecranTitreT;
		Sprite ecranTitre;

		Textbox textbox;
		Textbox textboxUsername;
		Textbox textboxErreur; // Ce textbox agit plutôt comme un messagebox.
		Font font;

		//Nécessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;		
		//Dictionaire de la sélection de menu
		std::map<char, bool> boutonMenu = { std::make_pair('1',false),std::make_pair('2',false) };
		//Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
		Textbox* textboxActif = nullptr;		
	};
}
