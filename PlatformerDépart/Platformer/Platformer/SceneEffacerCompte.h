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
		//L'�cran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Sprite ecranTitre;

		Text textMessage;
		Textbox textbox;
		Textbox textboxUsername;
		Textbox textboxErreur; // Ce textboxUser agit plut�t comme un messagebox.
		std::string userSupprimer;
							   //N�cessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;
		//Ne fait pas beaucoup sens � un Textbox, mais � plusieurs, �a le fera.
		Textbox* textboxActif = nullptr;
		
	};
}