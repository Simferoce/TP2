#include "Enemy.h"

using namespace platformer;
const std::string Enemy::texturePath = "Ressources\\Sprites\\MonsterA\\Idle.png";
int* Enemy::nbreImageParAnime = new int[nbreAnime] { 1, 10, 11, 11, 11 };

Enemy::Enemy() :Personnage(texturePath, nbreImageParAnime), velocity(0, 0)
{
}

Enemy::~Enemy()
{
	//delete[] anime;
}

bool Enemy::init(const int limiteGauche, const int limiteDroite)
{
	Personnage::init(limiteGauche, limiteDroite);
	anime = new Animation[nbreAnime];
	sensJoueurEst = Face;
	anime[Enemy::Attend] = Animation(nbreImageParAnime[Enemy::Attend], Enemy::Attend, TAILLE_RECT, TAILLE_RECT);
	anime[Enemy::Cours] = Animation(nbreImageParAnime[Enemy::Cours], Enemy::Cours, TAILLE_RECT, TAILLE_RECT);
	anime[Enemy::Saute] = Animation(nbreImageParAnime[Enemy::Saute], Enemy::Saute, TAILLE_RECT, TAILLE_RECT);
	anime[Enemy::Celebre] = Animation(nbreImageParAnime[Enemy::Celebre], Enemy::Celebre, TAILLE_RECT, TAILLE_RECT);
	anime[Enemy::Meurt] = Animation(nbreImageParAnime[Enemy::Meurt], Enemy::Meurt, TAILLE_RECT, TAILLE_RECT);
	animationActive = Attend;
	animateur = 0;
	nbreFrameParImageAnimation = 3.0f;
	ChangerTexture(Enemy::AnimationEnum::Cours, 1, Droite);

	return true;
}

void platformer::Enemy::Jump()
{
	if (!jumped) velocity.y = -9;
	jumped = true;
}


void platformer::Enemy::UpdateTexture(const int animation)
{

	if (animation == animationActive)
	{
		if (jumped)
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
		animationActive = (AnimationEnum)animation;
	}
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

