#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace platformer
{	
	/// <summary>
	/// Nouvelle version de la classe game.  � pr�sent elle sera surtout charg�e de charger les diff�rentes sc�nes
	/// testTest est toujours pr�sent pour que vous puissez faire le lien avec les test unitaires
	/// </summary>
	class Game
	{
	public:
		Game();
		int run();
		int testTest();
		bool init();
		static std::string userConnected;
	private:
		const int LARGEUR = 800;
		const int HAUTEUR = 480;
		;
		RenderWindow mainWin;
		Event event;
	};
}