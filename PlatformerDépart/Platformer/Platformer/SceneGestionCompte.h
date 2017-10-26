#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include <string>


using namespace std;
using namespace sf;

namespace platformer
{
	class SceneGestionCompte : public Scene
	{
	public:
		SceneGestionCompte();
		~SceneGestionCompte();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		char* pointATrouver;
		string utilisateur;
		string ligne;

		//Test de texte à l'écran
		sf::Text text;

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
		std::map<Keyboard::Key, bool> boutonMenu = { std::make_pair(Keyboard::Key::Num1,false),std::make_pair(Keyboard::Key::Num2,false) };
		//Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
		Textbox* textboxActif = nullptr;
	};
}
