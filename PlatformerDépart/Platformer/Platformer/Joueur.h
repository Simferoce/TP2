#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
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
	class Joueur : public Sprite
	{
		static const int nbreAnime = 5;
	public:
		enum AnimationEnum { Attend, Cours, Saute, Celebre, Meurt };
		AnimationEnum animationActive;
		int animateur;
		float nbreFrameParImageAnimation;
		enum Direction { Droite, Gauche, Face};
		Direction sensJoueurEst;
		static const int nbreImageParAnime[];
		Joueur();
		~Joueur();
		void move(const float offSetX, const float offSetY);
		bool init(const int limiteGauche, const int limiteDroite);
		void Jump();		
		/// <summary>
		/// Changer la Texture. Peut lancer exception de type invalid_argument si l'index est sup�rieur ou �gale au nombre d'images.
		/// </summary>
		/// <param name="animation">The animation.</param>
		/// <param name="index">The index.</param>
		/// <param name="direction">The direction.</param>
		void ChangerTexture(const AnimationEnum animation, const int index, const Direction direction);
		void UpdateTexture(const AnimationEnum animation);
		Vector2f velocity;
		bool jumped = false;
		float vitesse = 3;
	private:
		struct Animation
		{
			int nbreAnime;
			IntRect* tabAnime;
			Animation(int nbreAnime = 0, int IndexAnimeY = 0, int tailleX = 0, int tailleY = 0): nbreAnime(nbreAnime)
			{
				tabAnime = new IntRect[nbreAnime];
				for(int i = 0; i < nbreAnime; i++)
				{
					tabAnime[i] = IntRect(i * TAILLE_RECT, IndexAnimeY * TAILLE_RECT, TAILLE_RECT, TAILLE_RECT);
				}
			};
			~Animation()
			{
				delete[] tabAnime;
			}
			Animation& operator=(const Animation& other)
			{
				delete[] tabAnime;
				tabAnime = new IntRect[other.nbreAnime];
				for(int i = 0; i < other.nbreAnime; ++i)
				{
					tabAnime[i] = other.tabAnime[i];
				}
				nbreAnime = other.nbreAnime;
				return *this;
			};
			/// <summary>
			/// Obtient l'image correspondant � l'index sp�cifi�. L'index 0 �tant invalide, et le signe �tant le signe de l'image
			/// </summary>
			/// <param name="index">The index.</param>
			/// <returns></returns>
			IntRect operator[](const int index) const
			{
				if (abs(index) > nbreAnime || index == 0)
					throw std::invalid_argument("Impossible de r�cupr�rer l'image, index invalide. L'index ne peut pas �tre �gale � 0 et il doit se situ� entre " + std::to_string(nbreAnime *-1) + " et " + std::to_string(nbreAnime) + " inclusivement.");
				if (index > 0)
					return tabAnime[index - 1];
				IntRect inverse = tabAnime[abs(index) - 1];
				inverse.left = inverse.left + inverse.width;
				inverse.width *= -1;
				return inverse;
			};
		};
		static const int TAILLE_RECT = 64;
		static const std::string texturePath;
		Texture texture;

		Animation anime[nbreAnime];

		float limiteGauche;
		float limiteDroite;
	};
}

