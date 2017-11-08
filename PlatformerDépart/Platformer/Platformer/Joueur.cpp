#include "Joueur.h"

using namespace platformer;
const std::string Joueur::texturePath = "Ressources\\Sprites\\Player\\Player.png";
const int Joueur::nbreImageParAnime[] = { 1,10,11,11,11 };

Joueur::Joueur() : velocity(0,0)
{
}

Joueur::~Joueur()
{
}

bool Joueur::init(const int limiteGauche, const int limiteDroite)
{

	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
	sensJoueurEst = Face;
	anime[Joueur::Attend] = Animation(nbreImageParAnime[Joueur::Attend], Joueur::Attend,TAILLE_RECT,TAILLE_RECT);
	anime[Joueur::Cours] = Animation(nbreImageParAnime[Joueur::Cours], Joueur::Cours, TAILLE_RECT, TAILLE_RECT);
	anime[Joueur::Saute] = Animation(nbreImageParAnime[Joueur::Saute], Joueur::Saute, TAILLE_RECT, TAILLE_RECT);
	anime[Joueur::Celebre] = Animation(nbreImageParAnime[Joueur::Celebre], Joueur::Celebre, TAILLE_RECT, TAILLE_RECT);
	anime[Joueur::Meurt] = Animation(nbreImageParAnime[Joueur::Meurt], Joueur::Meurt, TAILLE_RECT, TAILLE_RECT);
	animationActive = Attend;
	animateur = 0;
	nbreFrameParImageAnimation = 3.0f;
	ChangerTexture(Joueur::AnimationEnum::Cours, 1, Droite);
	setTexture(texture);

	this->limiteGauche = limiteGauche;
	this->limiteDroite = limiteDroite;

	return true;
}

void platformer::Joueur::Jump()
{	
	if(!jumped) velocity.y = -9;
	jumped = true;
}

void platformer::Joueur::ChangerTexture(const AnimationEnum animation, const int index, const Direction direction)
{
	if(direction == Droite)
		setTextureRect(this->anime[animation][index*-1]);
	else
		setTextureRect(this->anime[animation][index]);
}

void platformer::Joueur::UpdateTexture(const AnimationEnum animation)
{

	if(animation == animationActive)
	{
		if(jumped)
		{
			nbreFrameParImageAnimation = 1.0f;
			ChangerTexture(AnimationEnum::Saute, animateur / (int)nbreFrameParImageAnimation % (nbreImageParAnime[AnimationEnum::Saute]) + 1, sensJoueurEst);
			if (animateur / (int)nbreFrameParImageAnimation % (nbreImageParAnime[AnimationEnum::Saute]) + 1 < 5) animateur++;
		}
		else
		{
			nbreFrameParImageAnimation = 3.0f;
			ChangerTexture(animation, animateur / (int)nbreFrameParImageAnimation % (nbreImageParAnime[animation]) + 1, sensJoueurEst);
			animateur++;
			if (animateur >= nbreImageParAnime[animation] * nbreFrameParImageAnimation)
				animateur = 0;
		}
	}
	else
	{
		nbreFrameParImageAnimation = 3.0f;
		animateur = 0;
		ChangerTexture(animation, 1, sensJoueurEst);
		animationActive = animation;
	}
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

