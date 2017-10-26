#include "SceneScore.h"
#include "Controle.h"
using namespace platformer;

SceneScore::SceneScore()
{

}

SceneScore::~SceneScore()
{
}

Scene::scenes SceneScore::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneScore::init(RenderWindow * const window)
{

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}
	for(int i =0; i < TABLEAU_SCORE_X; i++)
	{
		for(int j = 0; j < TABLEAU_SCORE_Y; j++)
		{
			tableauScore[i][j].setFont(font);
			tableauScore[i][j].setString("TEST");
			tableauScore[i][j].setPosition(DISTANCE_ENTRE_SCORE_X*i + POSITION_BASE_SCORE_X, DISTANCE_ENTRE_SCORE_Y*j + POSITION_BASE_SCORE_Y);
			tableauScore[i][j].setCharacterSize(Scene::GROSSEUR_CARACTERE);
			tableauScore[i][j].setFillColor(Scene::TEXTE_COULEUR);
			tableauScore[i][j].setStyle(Scene::TEXTE_STYLE);
		}
	}
	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'écran
	textboxUser.init(LARGEUR_TEXT, HAUTEUR_TEXT, Vector2f(POSITION_TEXTBOX_X, POSITION_TEXTBOX_USER_Y), font);
	textboxScore.init(LARGEUR_TEXT, HAUTEUR_TEXT, Vector2f(POSITION_TEXTBOX_X, POSITION_TEXTBOX_PASSWORD_Y), font);
	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneScore::getInputs()
{
	enterActif = false;
	backspaceActif = false;
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textboxUser avec la souris
			if (textboxUser.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxUser; //Ce textboxUser devient actif
				textboxUser.selectionner();  //on l'affiche comme étant sélectionné
			}
			else
			{
				//Sinon aucun textboxUser actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textboxUser.
				if (textboxActif != nullptr)
					textboxActif->deSelectionner();
				textboxActif = nullptr;
			}
		}
		if (event.type == Event::KeyPressed)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère
			}
		}
		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
		}
		if (event.type == Event::KeyPressed && textboxActif == nullptr)
		{
			if (event.key.code == Keyboard::Key::Escape)
			{
				transitionVersScene = Scene::scenes::TITRE;
				isRunning = false;
			}
		}
		//Attention : TextEntered est différent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.4/window-events-fr.php
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre à vous d'aller plus loin si vous voulez)
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
}

void SceneScore::update()
{
}

void SceneScore::draw()
{
	mainWin->clear();
	for (Text element : tableauScore[tableauScoreReprensantation::Utilisateur])
	{
		mainWin->draw(element);
	}
	for (Text element : tableauScore[tableauScoreReprensantation::Score])
	{
		mainWin->draw(element);
	}
	textboxUser.dessiner(mainWin);
	textboxScore.dessiner(mainWin);
	mainWin->display();
}
