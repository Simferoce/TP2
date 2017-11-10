#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "Personnage.h"
using namespace sf;

/// <summary>
/// Squelette d'une classe joueur.  Y a pas grand chose ici, mais c'est tout de même la sprite
/// De l'ensemble des animations qui est utilisée.
///
///QUATRES CONSEILS IMPORTANTS:
///1- Vous aurez le choix entre animer la spriteSheet ou d'intégrer 4 sprites différentes.  Dans ce cas-ci, votre 
///joueur ne devra plus hériter de sprite
///
///2- Si vous faites plus d'un niveau, le joueur pourrait être portée dans la game et passé par référence plutôt que détruit et crée à chaque niveau de jeu.
///
///3- Pour faire changer votre personnage direction, il faudra le "refléter dans une direction (reflet == scaling à -1)
///
///4- Si vous utilisez les sprites founis pour le joueur et que vous utilisez le cadre du Rectangle de sprite pour vos collisions, vos collisions seront probablement très éloignées.
///Votre jouuer pourrait "porter" un rectangle de collsion faisait 32 pixels de large.
///
/// </summary>
namespace platformer
{
	class Bloc;
	class Enemy : public Personnage
	{

	public:
		enum AnimationEnum { Attend, Cours, Saute, Celebre, Meurt };
		AnimationEnum animationActive;
		Enemy();
		~Enemy();
		virtual void move(const float offSetX, const float offSetY) override;
		virtual bool init(const int limiteGauche, const int limiteDroite) override;
		void Jump();
		/// <summary>
		/// Changer la Texture. Peut lancer exception de type invalid_argument si l'index est supérieur ou égale au nombre d'images.
		/// </summary>
		/// <param name="animation">The animation.</param>
		/// <param name="index">The index.</param>
		/// <param name="direction">The direction.</param>
		virtual void UpdateTexture(const int animation) override;
		Vector2f velocity;
		bool jumped = false;
		float vitesse = 3;
	private:
		static const std::string texturePath;
		static int* nbreImageParAnime;
		static const int nbreAnime = 5;
	};
}