#pragma once
#include <SFML/Graphics/Sprite.hpp>

class Bloc :
	public sf::Sprite
{
public:
	Bloc(sf::Texture& texture);
	~Bloc();
};

