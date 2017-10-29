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
	class SceneCreerCompte : public Scene
	{
	public:
		SceneCreerCompte();
		~SceneCreerCompte();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		std::vector<std::string> information;
		string ligne;

		//Text textLine;
		//Test de texte à l'écran
		
		Text text1;
		Text text2;
		Text text3;
		Text text4;
		Text text5;
		Text text6;
		string texteUtilisateur = "Utilisateur";
		string texteMotDePasse = "Mot de passe";
		string textePrenom = "Prenom";
		string texteNom = "Nom";
		string texteCourriel = "Courriel";

		//L'écran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.

		Textbox textbox;
		Textbox textboxUsername;
		Textbox textboxFirstName;
		Textbox textboxLastName;
		Textbox textboxEmail;
		Textbox textboxErreur; // Ce textbox agit plutôt comme un messagebox.
		Font font;

		//Nécessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;
		//Dictionaire de la sélection de menu
		std::map<Keyboard::Key, bool> boutonMenu = { std::make_pair(Keyboard::Key::Num1,false),std::make_pair(Keyboard::Key::Num2,false) };
		//Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
		Textbox* textboxActif = nullptr;

		bool VerifierNom(string prenom, int taille);
		bool VerifierCourriel(string courriel, int taille);
		bool VerifierMotDePasse(string courriel, int taille);
		bool VerifierUtilisateur(string utilisateur, int taille);
		int dernierePositionPoint;
		int positionArobas;
		int nbFoisArobas;
		//charactères mot de passe
		int nbMinuscule;
		int nbMajuscule;
		int nbChiffres;
		int nbCharSpecial;
		//username
		ifstream iFich;
	};
}
