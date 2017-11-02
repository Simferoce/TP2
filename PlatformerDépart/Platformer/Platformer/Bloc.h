#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
namespace platformer
{
	class Bloc :
		public sf::Sprite
	{
	public:
		enum Collision { Top, Bot, Right, Left, None, CollisionWithNoDeterminateSide };
		Collision DetermineCollision(sf::FloatRect other, sf::Vector2f deplacementPerFrameObjectOther);
		Bloc(sf::Texture& texture);
		~Bloc();
	};
}
