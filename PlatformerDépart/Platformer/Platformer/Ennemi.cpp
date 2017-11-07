#include "Ennemi.h"

using namespace platformer;

Enemy::Enemy() : velocity(0, 0), persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
	
}

Enemy::~Enemy()
{
	
}

void Enemy::move(const float offSetX, const float offSetY)
{

	Sprite::move(offSetX, offSetY);
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