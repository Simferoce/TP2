#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include <string>
#include <vector>


using namespace std;
using namespace sf;

namespace platformer
{
	class SceneModifierCompte : public Scene
	{
	public:
		SceneModifierCompte();
		~SceneModifierCompte();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		std::vector<std::string> information;
		string ligne;

		//Test de texte � l'�cran
		sf::Text text;

		//L'�cran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Texture ecranTitreT;
		Sprite ecranTitre;

		Textbox textbox;
		Textbox textboxUsername;
		Textbox textboxErreur; // Ce textbox agit plut�t comme un messagebox.
		Font font;

		//N�cessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;
		//Dictionaire de la s�lection de menu
		std::map<Keyboard::Key, bool> boutonMenu = { std::make_pair(Keyboard::Key::Num1,false),std::make_pair(Keyboard::Key::Num2,false) };
		//Ne fait pas beaucoup sens � un Textbox, mais � plusieurs, �a le fera.
		Textbox* textboxActif = nullptr;
	};
}
