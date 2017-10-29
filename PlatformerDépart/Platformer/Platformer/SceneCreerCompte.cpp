
#include <algorithm>
#include <fstream>
#include "Modele.h"
#include "SceneCreerCompte.h"

using namespace platformer;

SceneCreerCompte::SceneCreerCompte()
{

}

SceneCreerCompte::~SceneCreerCompte()
{
}

Scene::scenes SceneCreerCompte::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneCreerCompte::init(RenderWindow * const window)
{
	iFich.open("userpass.txt");
	if (!iFich.is_open())
	{
		//cout << "Fichier au mauvais endroit" << endl;
		return false;
	}
	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	//test de texte à l'écran
	text1=Modele::CreateTextLine("Veuiller entrer vos informations.",0,0);
	text2=Modele::CreateTextLine(texteUtilisateur, 0, 100);
	text3=Modele::CreateTextLine(texteMotDePasse, 0, 150);
	text4=Modele::CreateTextLine(textePrenom, 0, 200);
	text5=Modele::CreateTextLine(texteNom, 0, 250);
	text6=Modele::CreateTextLine(texteCourriel, 0, 300);
	
	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'écran
	textboxUsername.init(480, 24, Vector2f(430, 110), font);
	textbox.init(480, 24, Vector2f(430, 160), font);
	textboxFirstName.init(480, 24, Vector2f(430, 210), font);
	textboxLastName.init(480, 24, Vector2f(430, 260), font);
	textboxEmail.init(480, 24, Vector2f(430, 310), font);
	textboxErreur.initInfo(Vector2f(430, 400), font, true);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneCreerCompte::getInputs()
{
	enterActif = false;
	backspaceActif = false;
	for (auto iter = boutonMenu.begin(); iter != boutonMenu.end(); ++iter)
		iter->second = false;
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
			//Si on touche à la textbox avec la souris
			if (textbox.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textbox; //Ce textbox devient actif
				textbox.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxUsername.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxUsername; //Ce textbox devient actif
				textboxUsername.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxFirstName.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxFirstName; //Ce textbox devient actif
				textboxFirstName.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxLastName.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxLastName; //Ce textbox devient actif
				textboxLastName.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxEmail.touche(Mouse::getPosition(*mainWin)))
			{
				if (textboxActif != nullptr) textboxActif->deSelectionner();
				textboxActif = &textboxEmail; //Ce textbox devient actif
				textboxEmail.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				if(textboxActif!=nullptr)
				{
					textboxActif->deSelectionner();
					textboxActif = nullptr;
				}	
			}
		}
		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère


			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
		}
		if (event.type == Event::KeyPressed && textboxActif == nullptr)
		{
			//On n'a pas besoin d'une touche pour aller sur la page qu'on est déjà
			if (event.key.code == Keyboard::Num1)
			{
				boutonMenu[Keyboard::Key::Num1] = true;
				isRunning = false;
				transitionVersScene = Scene::scenes::GESTIONCOMPTE;
			}
			if (event.key.code == Keyboard::Num2) {
				//isRunning = false;
				//transitionVersScene = Scene::scenes::GESTIONCOMPTE;
			}
			else if (event.key.code == Keyboard::Num2)
			{
				boutonMenu[Keyboard::Key::Num2] = true;
			}
			else if (event.key.code == Keyboard::Num3)
			{
				boutonMenu[Keyboard::Key::Num3] = true;
			}
		}
		const auto menuBoutonChoisi = std::find_if(boutonMenu.begin(), boutonMenu.end(), [](std::pair<Keyboard::Key, bool> n) { return n.second == true; });
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

void SceneCreerCompte::update()
{
	if (enterActif)
	{
		if (VerifierUtilisateur(textboxUsername.getTexte(),textboxUsername.getTexte().getSize()))
		{
			if(VerifierMotDePasse(textbox.getTexte(),textbox.getTexte().getSize()))
			{
				if(VerifierNom(textboxFirstName.getTexte(),textboxFirstName.getTexte().getSize()))
				{
					if(VerifierNom(textboxLastName.getTexte(),textboxLastName.getTexte().getSize()))
					{
						if(VerifierCourriel(textboxEmail.getTexte(),textboxEmail.getTexte().getSize()))
						{
							textboxErreur.insererTexte("Les conditions fonctionnent pour l'instant.");
						}
						else
						{
							textboxErreur.insererTexte("Adresse de courriel incorrecte");
						}
					}
					else
					{
						textboxErreur.insererTexte("Nom incorrect");
					}
				}
				else
				{
					textboxErreur.insererTexte("Prenom incorrect");
				}
			}
			else
			{
				textboxErreur.insererTexte("Mot de passe incorrect");
			}
		}
		else
		{
			textboxErreur.insererTexte("Nom d'utilisateur incorrect");
		}
	}
}

void SceneCreerCompte::draw()
{
	mainWin->clear();
	textbox.dessiner(mainWin);
	textboxUsername.dessiner(mainWin);
	textboxErreur.dessiner(mainWin);
	textboxFirstName.dessiner(mainWin);
	textboxLastName.dessiner(mainWin);
	textboxEmail.dessiner(mainWin);
	//test texte à l'écran
	// puis, dans la boucle de dessin, entre window.clear() et window.display()
	mainWin->draw(text1);
	mainWin->draw(text2);
	mainWin->draw(text3);
	mainWin->draw(text4);
	mainWin->draw(text5);
	mainWin->draw(text6);

	mainWin->display();
}
bool SceneCreerCompte::VerifierNom(string prenom, int taille)
{
	if(taille<2 || taille>25)
	{
		return false;
	}
	for(int i=0;i<taille;i++)
	{
		if(prenom[i]!='-' && prenom[i]!='.' && (prenom[i]<'a' || prenom[i]>'z') && (prenom[i]<'A' || prenom[i]>'Z'))
		{
			return false;
		}
	}
	return true;
}
bool SceneCreerCompte::VerifierCourriel(string courriel, int taille)
{
	nbFoisArobas = 0;
	positionArobas = 0;
	dernierePositionPoint = 0;
	if (strstr(courriel.c_str(),".com") || strstr(courriel.c_str(), ".ca"))
	{

	}
	else
	{
		return false;
	}
	for(int i=0;i<taille;i++)
	{
		if(courriel[i]=='@')
		{
			nbFoisArobas++;
			positionArobas = i;
		}
		else if(courriel[i]=='.')
		{
			dernierePositionPoint = i;
		}
		else if((courriel[i]<'a' || courriel[i]>'z') && (courriel[i]<'A' || courriel[i]>'Z') && courriel[i]!='_' && courriel[i]!='-')
		{
			return false;
		}
	}
	if(nbFoisArobas!=1 || positionArobas>dernierePositionPoint)
	{
		return false;
	}
	return true;
}
bool SceneCreerCompte::VerifierMotDePasse(string courriel, int taille)
{
	if(taille<5 || taille>15)
	{
		return false;
	}
	for(int i=0;i<taille;i++)
	{
		if(courriel[i]>='a' && courriel[i]<='z')
		{
			nbMinuscule++;
		}
		else if(courriel[i] >= 'A' && courriel[i] <= 'Z')
		{
			nbMajuscule++;
		}
		else if(courriel[i] >= '0' && courriel[i] <= '9')
		{
			nbChiffres;
		}
		else
		{
			nbCharSpecial++;
		}
	}
	if(nbMinuscule<1 || nbMajuscule<1 || nbChiffres<1 || nbCharSpecial<1)
	{
		return false;
	}
	return true;
}
//La vérification n'est pas complète
bool SceneCreerCompte::VerifierUtilisateur(string utilisateur, int taille)
{
	if(taille<3 || taille>25)
	{
		return false;
	}
	
	while(getline(iFich, ligne))
	{
		information = Modele::split(ligne, ':');
		if(utilisateur==information[Modele::Nickname])
		{
			return false;
		}
	}
	return true;
}

