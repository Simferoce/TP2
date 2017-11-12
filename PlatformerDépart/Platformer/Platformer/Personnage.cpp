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
/// <summary>
/// Initialise.
/// </summary>
/// <param name="limiteGauche">limite gauche.</param>
/// <param name="limiteDroite">limite droite.</param>
/// <returns></returns>
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
/// <summary>
/// Changer la texture des personnages
/// </summary>
/// <param name="animation">animation.</param>
/// <param name="index">index.</param>
/// <param name="direction">direction.</param>
void platformer::Personnage::ChangerTexture(const int animation, const int index, const Direction direction)
{
	//On fait l'animation juste pour le joueur, on garde la même image pour les ennemis
	if(texturePath=="Ressources\\Sprites\\Player\\Player.png")
	{
		if (direction == Droite)
			setTextureRect(this->anime[animation][index*-1]);
		else
			setTextureRect(this->anime[animation][index]);
	}
	else
	{
		setTextureRect(this->anime[0][1]);
	}
	
}

void platformer::Personnage::UpdateTexture(const int animation)
{

}
/// <summary>
/// Deplace le personnage
/// </summary>
/// <param name="offSetX">off set x.</param>
/// <param name="offSetY">off set y.</param>
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
