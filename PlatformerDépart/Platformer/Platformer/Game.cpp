#include "Game.h"
#include "SceneLogin.h"
#include "SceneNiveau1.h"
#include "SceneGestionCompte.h"
#include "SceneCreerCompte.h"
#include "Controle.h"
#include "SceneTitre.h"
#include "SceneScore.h"
#include "SceneModifierCompte.h"
#include "SceneEffacerCompte.h"

using namespace platformer;
std::string Game::userConnected = "";
Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner
	mainWin.create(VideoMode(LARGEUR, HAUTEUR, 32), "Platformer");  // , Style::Titlebar); / , Style::FullScreen);
	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

int Game::testTest()
{
	return 0;
}

int Game::run()
{
	//deux enums et un pointeur de scene pour faire la manipulation de sc�ne
	Scene::scenes selecteurDeScene = Scene::scenes::NIVEAU1;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle sc�ne
	while (true)
	{

		//Seule condition de sortie de toute l'app
		if (selecteurDeScene == Scene::scenes::SORTIE)
		{
			Controle::Decharger();
			Modele::Decharger();
			Gem::decharger();
			return EXIT_SUCCESS;
		}
		else			
		{
			//Vous allez ajouter d'autre sc�nes, alors elles devront
			//�tre ajout�es ici
			mainWin.setView(mainWin.getDefaultView());
			switch (selecteurDeScene)
			{
			case Scene::scenes::TITRE:
				sceneActive = new SceneTitre();
				break;
			case Scene::scenes::LOGIN:
				sceneActive = new SceneLogin();
				break;
			case Scene::scenes::GESTIONCOMPTE:
				sceneActive = new SceneGestionCompte();
				break;
			case Scene::scenes::NIVEAU1:
				sceneActive = new SceneNiveau1();
				break;
			case Scene::scenes::SCORE:
				sceneActive = new SceneScore();
				break;
			case Scene::scenes::CREERCOMPTE:
				sceneActive = new SceneCreerCompte();
				break;
			case Scene::scenes::MODIFIERCOMPTE:
				sceneActive = new SceneModifierCompte();
				break;
			case Scene::scenes::EFFACERCOMPTE:
				sceneActive = new SceneEffacerCompte();
			}
			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
				//� la fin d'une sc�ne, s'il y a des sauvegardes � faire
				//C'est aussi possible de les faire l�.
				if (SceneNiveau* niveau = dynamic_cast<SceneNiveau*>(sceneActive))
				{
					Controle::AjouterScore(Game::userConnected, niveau->GetScore(), Modele::GetSaveEmplacement());
					Modele::Save(Modele::GetSaveEmplacement());
					userConnected = "";
					niveau->Decharger();
				}
			}
			else
			{
				//cleap-up � faire pour s'assurer  de ne pas avoir de leak
				//(malgr� l'�chec)
				return EXIT_FAILURE;
			}			
		}

		selecteurDeScene = sceneEnRetour;
		delete sceneActive;
		sceneActive = nullptr;
	}
}

bool Game::init()
{
	if (!Modele::Init(Modele::GetSaveEmplacement()))
		return false;
	return true;
}
