#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
using namespace  sf;
namespace platformer
{
	class SceneEffacerCompte : public Scene
	{
	public:
		SceneEffacerCompte();
		~SceneEffacerCompte();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
	private:
		//L'écran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Sprite ecranTitre;

		Text textMessage;
		Textbox textbox;
		Textbox textboxUsername;
		Textbox textboxErreur; // Ce textboxUser agit plutôt comme un messagebox.
		std::string userSupprimer;
							   //Nécessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;
		//Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
		Textbox* textboxActif = nullptr;
		
	};
}