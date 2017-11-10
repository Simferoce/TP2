#include "Personnage.h"

using namespace platformer;

Personnage::Personnage(std::string texturePath, int nbreImageParAnime[]) : velocity(0, 0)
{
	this->texturePath = texturePath;
	this->nbreImageParAnime = nbreImageParAnime;
	nbreFrameParImageAnimation = 3.0f;
	animateur = 0;
}

Personnage::~Personnage()
{
}

bool Personnage::init(const int limiteGauche, const int limiteDroite)
{

	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
	setTexture(texture);

	this->limiteGauche = limiteGauche;
	this->limiteDroite = limiteDroite;

	return true;
}

void platformer::Personnage::ChangerTexture(const int animation, const int index, const Direction direction)
{
	if (direction == Droite)
		setTextureRect(this->anime[animation][index*-1]);
	else
		setTextureRect(this->anime[animation][index]);
}

void platformer::Personnage::UpdateTexture(const int animation)
{

}

void Personnage::move(const float offSetX, const float offSetY)
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
