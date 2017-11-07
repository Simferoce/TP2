#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
namespace  platformer
{
	class Bloc;
	class Enemy:public Sprite
	{
	public:
		enum typeEnemy {MEN,ZOMBIE,MENJUMP};
		Enemy();
		~Enemy();
		void move(const float offSetX, const float offSetY);
		Vector2f velocity;
		float vitesse = 3;
		static int sizeNumberEnemies;
		typeEnemy GetType();
	protected:
		typeEnemy typeEquipe;
		IntRect persoRect;
		float limiteGauche;
		float limiteDroite;
	private:
		static const int TAILLE_RECT = 64;
	};
}