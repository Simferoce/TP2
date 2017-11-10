#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
using namespace sf;


namespace platformer
{
	class Bloc;
	class Personnage : public Sprite
	{
	protected:
		int nbreAnime;
		struct Animation
		{
			int nbreAnime;
			IntRect* tabAnime;
			Animation(int nbreAnime = 0, int IndexAnimeY = 0, int tailleX = 0, int tailleY = 0) : nbreAnime(nbreAnime)
			{
				tabAnime = new IntRect[nbreAnime];
				for (int i = 0; i < nbreAnime; i++)
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
				for (int i = 0; i < other.nbreAnime; ++i)
				{
					tabAnime[i] = other.tabAnime[i];
				}
				nbreAnime = other.nbreAnime;
				return *this;
			};
			/// <summary>
			/// Obtient l'image correspondant à l'index spécifié. L'index 0 étant invalide, et le signe étant le signe de l'image
			/// </summary>
			/// <param name="index">The index.</param>
			/// <returns></returns>
			IntRect operator[](const int index) const
			{
				if (abs(index) > nbreAnime || index == 0)
					throw std::invalid_argument("Impossible de récuprérer l'image, index invalide. L'index ne peut pas être égale à 0 et il doit se situé entre " + std::to_string(nbreAnime *-1) + " et " + std::to_string(nbreAnime) + " inclusivement.");
				if (index > 0)
					return tabAnime[index - 1];
				IntRect inverse = tabAnime[abs(index) - 1];
				inverse.left = inverse.left + inverse.width;
				inverse.width *= -1;
				return inverse;
			};
		};
		static const int TAILLE_RECT = 64;
		std::string texturePath;
		Texture texture;
		Animation* anime;
		float limiteGauche;
		float limiteDroite;
	public:

		int animateur;
		float nbreFrameParImageAnimation;
		enum Direction { Droite, Gauche, Face };
		Direction sensJoueurEst;
		int* nbreImageParAnime;
		Personnage(std::string texturePath, int nbreImageParAnime[]);
		~Personnage();
		virtual void move(const float offSetX, const float offSetY);
		virtual bool init(const int limiteGauche, const int limiteDroite);
		/// <summary>
		/// Changer la Texture. Peut lancer exception de type invalid_argument si l'index est supérieur ou égale au nombre d'images.
		/// </summary>
		/// <param name="animation">The animation.</param>
		/// <param name="index">The index.</param>
		/// <param name="direction">The direction.</param>
		virtual void ChangerTexture(const int animation, const int index, const Direction direction);
		virtual void UpdateTexture(const int animation);
		Vector2f velocity;
		bool jumped = false;
		float vitesse = 3;
		
	};
}