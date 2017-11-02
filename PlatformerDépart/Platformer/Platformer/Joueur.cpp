#include "Joueur.h"

using namespace platformer;

Joueur::Joueur() : velocity(0,0), persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
}

Joueur::~Joueur()
{
}

bool Joueur::init(const int limiteGauche, const int limiteDroite, const String texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}

	setTexture(texture);
	setTextureRect(persoRect);

	this->limiteGauche = limiteGauche;
	this->limiteDroite = limiteDroite;

	return true;
}

void platformer::Joueur::jump()
{	
	if(!jumped) velocity.y = -5;
	jumped = true;
}

void Joueur::move(const float offSetX, const float offSetY)
{

	Sprite::move(offSetX,offSetY);
	//Test sur les limites de l'écran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x + getGlobalBounds().width > limiteDroite)
	{
		setPosition(limiteDroite - getGlobalBounds().width, getPosition().y);
	}
}

