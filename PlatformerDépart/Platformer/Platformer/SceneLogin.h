#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"


using namespace sf;

namespace platformer
{
	class SceneLogin: public Scene
	{
	public:
		SceneLogin();
		~SceneLogin();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		//L'�cran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Sprite ecranTitre;

		Textbox textbox;
		Textbox textboxUsername;
		Textbox textboxErreur; // Ce textboxUser agit plut�t comme un messagebox.

		//N�cessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;		
		//Ne fait pas beaucoup sens � un Textbox, mais � plusieurs, �a le fera.
		Textbox* textboxActif = nullptr;		
	};
}
