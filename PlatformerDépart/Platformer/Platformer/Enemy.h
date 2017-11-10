#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "Personnage.h"
using namespace sf;

/// <summary>
/// Squelette d'une classe joueur.  Y a pas grand chose ici, mais c'est tout de m�me la sprite
/// De l'ensemble des animations qui est utilis�e.
///
///QUATRES CONSEILS IMPORTANTS:
///1- Vous aurez le choix entre animer la spriteSheet ou d'int�grer 4 sprites diff�rentes.  Dans ce cas-ci, votre 
///joueur ne devra plus h�riter de sprite
///
///2- Si vous faites plus d'un niveau, le joueur pourrait �tre port�e dans la game et pass� par r�f�rence plut�t que d�truit et cr�e � chaque niveau de jeu.
///
///3- Pour faire changer votre personnage direction, il faudra le "refl�ter dans une direction (reflet == scaling � -1)
///
///4- Si vous utilisez les sprites founis pour le joueur et que vous utilisez le cadre du Rectangle de sprite pour vos collisions, vos collisions seront probablement tr�s �loign�es.
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
		/// Changer la Texture. Peut lancer exception de type invalid_argument si l'index est sup�rieur ou �gale au nombre d'images.
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